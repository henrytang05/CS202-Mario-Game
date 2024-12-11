#include "Map.h"
#include "Logger.h"
void TileFactory::addTileset(const std::string& tilesetPath, const std::string& imagePath, int firstgid) {
    std::ifstream file(tilesetPath );
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
        textureMap[i+firstgid] = tileTexture;
        UnloadImage(tileImage);
    }

    UnloadImage(tilesetImageAsImage);
    UnloadTexture(tilesetImage);
}

std::shared_ptr<GameObject> TileFactory::Create(int tileId, const std::string& type, Vector2 position) {
    if (textureMap.find(tileId) != textureMap.end()) {
        if (type == "Block") {
            std::cerr<<"Block found"<<endl;
            return std::make_shared<Block>(textureMap[tileId], position);
        }
        // else if (type == "Interact") {
        //     return std::make_shared<Interact>(textureMap[tileId], position);
        // }
    }
    return nullptr;
}

MapRenderer::MapRenderer(const std::string& mapPath, TileFactory& factory) {
    std::ifstream file(mapPath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << mapPath << std::endl;
        return;
    }
    json mapData;
       try {
        file >> mapData;
    } catch (const json::parse_error& e) {
        std::cerr << "Parse error: " << e.what() << std::endl;
        return;
    }

    if (mapData.is_null()) {
        std::cerr << "Error: JSON data is null" << std::endl;
        return;
    }

    mapWidth = mapData["width"];
    mapHeight = mapData["height"];
    tileWidth = mapData["tilewidth"];
    tileHeight = mapData["tileheight"];
    std::cerr << "Map width: " << mapWidth << " Map height: " << mapHeight << std::endl;
//Load Tilesets
    const std::string dir= "Map/";
    for(const auto& tileset: mapData["tilesets"]){
        int index = 0;
        int firstgid = tileset["firstgid"];
        std::cerr<<"firstgid: " << firstgid << std::endl;
        std::string tilesetPath = tileset["source"];
        std::cerr<<"tilesetPath: " << tilesetPath << std::endl;
        std::string imagePath = tilesetPath.substr(0,(int)tilesetPath.size()-5)+".png";
        std::cerr<<"imagePath: " << imagePath << std::endl;
        factory.addTileset(dir+tilesetPath, dir+imagePath, firstgid);
        std::cerr << "Tileset added: " << tilesetPath << std::endl;
    }


    for (const auto& layer : mapData["layers"]) {
        if (layer["type"] == "tilelayer") {
            LoadLayer(layer, factory);
        }
        else if (layer["type"] == "objectgroup") {
            //LoadObjectGroup(layer, factory);
        }
    }
}

void MapRenderer::LoadLayer(const json& layer, TileFactory& factory) {
    int index = 0;
    std::cerr<<"LoadLayer"<<index<<std::endl;
    for (const auto& tileIdValue : layer["data"]) {
        if (!tileIdValue.is_null() && tileIdValue.is_number()) {
            int tileId = tileIdValue.get<int>();
            int x = (index % mapWidth) * tileWidth;
            int y = (index / mapWidth) * tileHeight;
            //std::cerr<<"tileId"<<tileId<<endl;
            auto obj = factory.Create(tileId, "Block", { (float)x, (float)y });
            //std::cerr<<"Obj created successfully"<<endl;
            // std::cerr<<"tileId"<<tileId<<endl;
            if (obj) {
                objects.push_back(obj);
            }
        }
        index++;
    }
}

void MapRenderer::LoadObjectGroup(const json &layer, TileFactory &factory)
{

}

void MapRenderer::Render() {
    for (const auto& obj : objects) {
        obj->draw();
    }
}

