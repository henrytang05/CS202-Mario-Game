#include "Map.h"
#include "Logger.h"

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

    cerr<<"mapWidth: "<<mapWidth<<endl;
    string Level;
    for (const auto &properties : mapData["properties"]) {
            if (properties["name"] == "Level") {
                Level = properties["value"];
                break;
            }
        }


    //Load Tilesets
    std::string dir = "assets/" + Level; // This one will be changed as Level1, Level2
    for (const auto& tileset : mapData["tilesets"]) {
        std::string tilesetPath = dir + "/" + tileset["source"].get<std::string>();
        std::string imagePath = tilesetPath.substr(0, tilesetPath.find_last_of(".")) + ".png";
        std::cerr<<"tilesetPath: "<<tilesetPath<<std::endl;
        std::cerr<<"imagePath: "<<imagePath<<std::endl;
        int firstGid = tileset["firstgid"];
        TextureManager::getInstance().addTileset(tilesetPath, imagePath, firstGid);
    }

    // Load Layers
    for (const auto& layer : mapData["layers"]) {
        if (layer["type"] == "objectgroup") {
            loadObjectGroup(layer);
        }
    }
    return objects;
   
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
            for (auto const &property : object_layer["properties"]) {
                if(property["name"]=="height"){
                    height = property["value"];
                }
                if(property["name"]=="width"){
                    width = property["value"];
                }
            }
            auto obj = entityFactory->createPipe({x, y}, {width, height});
            if (obj) {
                objects.push_back(obj);
            }
        } else if (name == "Flag") {
            // Create an enemy object
            entityFactory = std::make_unique<EntityFactory>();
            auto obj = entityFactory->createFlag({x, y});
            if (obj) {
                objects.push_back(obj);
            }
        } else if (name == "FlagPole") {
            // Create an enemy object
            entityFactory = std::make_unique<EntityFactory>();
            auto obj = entityFactory->createFlagPole({x, y});
            if (obj) {
                objects.push_back(obj);
            }
        } else if (name == "NormalBlock"){
            entityFactory = std::make_unique<EntityFactory>();
            auto obj = entityFactory->createBlock("NormalBlock", {x, y});
            if (obj) {
                objects.push_back(obj);
            }
        } else if (name == "BrokenBlock"){
            entityFactory = std::make_unique<EntityFactory>();
            auto obj = entityFactory->createBlock("BrokenBlock", {x, y});
            if (obj) {
                objects.push_back(obj);
            }
        } else if (name == "HardBlock"){
            entityFactory = std::make_unique<EntityFactory>();
            auto obj = entityFactory->createBlock("HardBlock", {x, y});
            if (obj) {
                objects.push_back(obj);
            }
        } else if (name == "GroundBlock"){
            entityFactory = std::make_unique<EntityFactory>();
            auto obj = entityFactory->createBlock("GroundBlock", {x, y});
            if (obj) {
                objects.push_back(obj);
            }
        } else if (name == "QuestionBlock"){
            entityFactory = std::make_unique<EntityFactory>();
            auto obj = entityFactory->createBlock("QuestionBlock", {x, y});
            if(object_layer.find("properties") != object_layer.end()){
                for (auto const &property : object_layer["properties"]) {
                    if(property["name"]=="isCoin"){
                        if(property["value"]==true){
                            entityFactory = std::make_unique<EntityFactory>();
                            auto coin = entityFactory->createCoin({x, y});
                            if(coin){
                                objects.push_back(coin);
                                obj->addObserver(coin);                        
                            }
                        }
                    }
                    if(property["name"]=="isMushroom"){
                        if(property["value"]==true){
                            entityFactory = std::make_unique<EntityFactory>();
                            auto mushroom = entityFactory->createMushroom({x, y});
                            if(mushroom){
                                objects.push_back(mushroom);
                                obj->addObserver(mushroom);
                            }
                        }
                    }
                }
            }
            if (obj) {
                objects.push_back(obj);
            }
              
            
        } 
        else if (name == "Piranha"){
            entityFactory = std::make_unique<EntityFactory>();
            auto obj = entityFactory->createPiranha({x, y});
            if (obj) {
                objects.push_back(obj);
            }
        } 
        else if (name == "Mushroom"){
            entityFactory = std::make_unique<EntityFactory>();
            auto obj = entityFactory->createMushroom({x, y});
            if (obj) {
                objects.push_back(obj);
            }
        } else if (name == "Coin"){
            entityFactory = std::make_unique<EntityFactory>();
            auto obj = entityFactory->createCoin({x, y});
            if (obj) {
                objects.push_back(obj);
            }
        }
    }
}

void MapRenderer::render() {
  for (const auto &obj : objects) {
    obj->draw();
  }
}
