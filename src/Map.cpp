#include "Map.h"
#include "Logger.h"

std::vector<Weak<AbstractEntity>>
MapRenderer::createMap(const std::string &mapPath) {
  std::ifstream file(mapPath);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << mapPath << std::endl;
    return objects;
  }
  json mapData;
  try {
    file >> mapData;
  } catch (const json::parse_error &e) {
    std::cerr << "Parse error: " << e.what() << std::endl;
    return objects;
  }

  if (mapData.is_null()) {
    std::cerr << "Error: JSON data is null" << std::endl;
    return objects;
  }

  mapWidth = mapData["width"];
  mapHeight = mapData["height"];
  tileWidth = mapData["tilewidth"];
  tileHeight = mapData["tileheight"];

  cerr << "mapWidth: " << mapWidth << endl;
  string Level;
  for (const auto &properties : mapData["properties"]) {
    if (properties["name"] == "Level") {
      Level = properties["value"];
      break;
    }
  }

  // Load Tilesets
  std::string dir =
      "assets/" + Level; // This one will be changed as Level1, Level2
  for (const auto &tileset : mapData["tilesets"]) {
    std::string tilesetPath = dir + "/" + tileset["source"].get<std::string>();
    std::string imagePath =
        tilesetPath.substr(0, tilesetPath.find_last_of(".")) + ".png";
    std::cerr << "tilesetPath: " << tilesetPath << std::endl;
    std::cerr << "imagePath: " << imagePath << std::endl;
    int firstGid = tileset["firstgid"];
    TextureManager::getInstance().addTileset(tilesetPath, imagePath, firstGid);
  }

  // Load Layers
  for (const auto &layer : mapData["layers"]) {
    if (layer["type"] == "objectgroup") {
      loadObjectGroup(layer);
    }
  }
  return objects;
}

void MapRenderer::loadObjectGroup(const json &layer) {
  if (layer["type"] != "objectgroup") {
    std::cerr << "Layer is not of type objectgroup" << std::endl;
    return;
  }
  string name = layer["name"];

  entityFactory = std::make_unique<EntityFactory>(EM);
  const auto &object_layers = layer["objects"];
  for (const auto &object_layer : object_layers) {

    float x = object_layer["x"];
    float y = object_layer["y"];
    float width = object_layer["width"];
    float height = object_layer["height"];
    // Create game objects based on type
    if (name == "Pipe") {
      auto obj = entityFactory->createPipe({x, y}, {width, height});
      if (obj.lock()) {
        objects.push_back(obj);
      }
      std::cerr << "x: " << x << " y: " << y << std::endl;
      std::cerr << "width: " << width << " height: " << height << std::endl;
    } else if (name == "Flag") {
      // Create an enemy object
      auto obj = entityFactory->createFlag({x, y});
      if (obj.lock()) {
        objects.push_back(obj);
      }
    } else if (name == "FlagPole") {
      // Create an enemy object
      auto obj = entityFactory->createFlagPole({x, y});
      if (obj.lock()) {
        objects.push_back(obj);
      }
    } else if (name == "NormalBlock") {
      auto obj = entityFactory->createBlock("NormalBlock", {x, y});
      if (obj.lock()) {
        objects.push_back(obj);
      }
    } else if (name == "BrokenBlock") {
      auto obj = entityFactory->createBlock("BrokenBlock", {x, y});
      if (obj.lock()) {
        objects.push_back(obj);
      }
    } else if (name == "HardBlock") {
      auto obj = entityFactory->createBlock("HardBlock", {x, y});
      if (obj.lock()) {
        objects.push_back(obj);
      }
    } else if (name == "GroundBlock") {
      auto obj = entityFactory->createBlock("GroundBlock", {x, y});
      if (obj.lock()) {
        objects.push_back(obj);
      }
    } else if (name == "QuestionBlock") {
      auto obj = entityFactory->createBlock("QuestionBlock", {x, y});
      if (obj.lock()) {
        objects.push_back(obj);
      }
    }
    else if (name == "Goomba") {
      auto obj = entityFactory->createGoomba({x, y}, {16.0f, 16.0f});
      if (obj.lock()) {
        objects.push_back(obj);
      }
    }
  }
}

void MapRenderer::render() {
  // for (const auto &obj : objects) {
  //   obj->draw();
  // }
}
