#include "Map.h"
#include "Logger.h"

void MapRenderer::addTileset(const std::string& tilesetPath, const std::string& imagePath, int firstGid) {
    std::ifstream file(tilesetPath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << tilesetPath << std::endl;
        return;
    }
    json tilesetData;
    try {
        file >> tilesetData;
    } catch (const json::parse_error& e) {
        std::cerr << "Parse error: " << e.what() << std::endl;
        return;
    }

    Texture2D tilesetImage = LoadTexture(imagePath.c_str());
    Image tilesetImageAsImage = LoadImageFromTexture(tilesetImage);

    int tileWidth = tilesetData["tilewidth"];
    int tileHeight = tilesetData["tileheight"];
    int columns = tilesetData["columns"];
    int tileCount = tilesetData["tilecount"];

    // Create textures for each tile.
    for (int i = 0; i < tileCount; ++i) {
        float x = (i % columns) * tileWidth;
        float y = (i / columns) * tileHeight;
        Image tileImage = ImageFromImage(tilesetImageAsImage, { x, y, (float)tileWidth, (float)tileHeight });
        Texture2D tileTexture = LoadTextureFromImage(tileImage);
        textureMap[i + firstGid] = {"Null",tileTexture};
        UnloadImage(tileImage);
    }
    std::cerr<<"Still good her before add type"<<std::endl;
    // Add type for tiles
    //Base on the type in the json file
    if(tilesetData.find("tiles") == tilesetData.end()){
        return;
    }
    for(const auto& tile : tilesetData["tiles"]){
      int id = tile["id"];
    if (tile.contains("type")) {
        string type = tile["type"];
        textureMap[id + firstGid].first = type;
    }
    }

    UnloadImage(tilesetImageAsImage);
    UnloadTexture(tilesetImage);
}


std::vector<Shared<AbstractEntity>> MapRenderer::createMap(const std::string& mapPath) { 
    std::ifstream file(mapPath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << mapPath << std::endl;
        return objects;
    }
    json mapData;
    try {
        file >> mapData;
    } catch (const json::parse_error& e) {
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
    std::cerr << "Map width: " << mapWidth << " Map height: " << mapHeight << std::endl;

    // Load Tilesets
    const std::string dir = "Map/";
    for (const auto& tileset : mapData["tilesets"]) {
        int firstGid = tileset["firstgid"];
        std::string tilesetPath = tileset["source"];
        std::string imagePath = tilesetPath.substr(0, tilesetPath.size() - 5) + ".png";
        this->addTileset(dir + tilesetPath, dir + imagePath, firstGid);
    }
    
    // Load Layers
    for (const auto& layer : mapData["layers"]) {
        if (layer["type"] == "tilelayer") {
            loadLayer(layer);
        } else if (layer["type"] == "objectgroup") {
            loadObjectGroup(layer);
        }
    }

    return objects;
   
}
vector<Shared<AbstractEntity>> loadEntity() {
    return vector<Shared<AbstractEntity>>();
}
void MapRenderer::loadLayer(const json& layer) {
  std::cerr<<"load layer"<<std::endl;
    int index = 0;
    for (const auto& tileIdValue : layer["data"]) {
      if (!tileIdValue.is_null() && tileIdValue.is_number()) {
          int tileId = tileIdValue.get<int>();
          int x = (index % mapWidth) * tileWidth;
          int y = (index / mapWidth) * tileHeight;
          if(textureMap.find(tileId) == textureMap.end()){
              index++;
              continue;
          }
          if(textureMap[tileId].first == "Null"){
              index++;
              continue;
          }
          entityFactory = std::make_unique<EntityFactory>();
          auto obj = entityFactory->createBlock(textureMap[tileId].first,textureMap[tileId].second, { (float)x, (float)y });
          if (obj) {
              objects.push_back(obj);
              index++;
          }
        }
    }
}

void MapRenderer::loadObjectGroup(const json& layer) {
    if (layer["type"] != "objectgroup") {
        std::cerr << "Layer is not of type objectgroup" << std::endl;
        return;
    }
    string name = layer["name"];
    const auto& object_layers = layer["objects"];
    for (const auto& object_layer : object_layers) {
        
        float x = object_layer["x"];
        float y = object_layer["y"];
        float width = object_layer["width"];
        float height = object_layer["height"];

        //Create game objects based on type
        if (name == "Pipe") {
            entityFactory = std::make_unique<EntityFactory>();
            auto obj = entityFactory->createPipe({x, y}, {width, height});
            if (obj) {
                objects.push_back(obj);
            }
            std::cerr<<"x: "<<x<<" y: "<<y<<std::endl;
            std::cerr<<"width: "<<width<<" height: "<<height<<std::endl;
            
        } else if (name == "Flag") {
            // Create an enemy object
            entityFactory = std::make_unique<EntityFactory>();
            auto obj = entityFactory->createFlag({x, y});
            if (obj) {
                objects.push_back(obj);
            }
        } 
        else 
        {
            return;
        }
    }
}

void MapRenderer::render() {
    for (const auto& obj : objects) {
        obj->draw();
    }
}
