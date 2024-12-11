#include "Map.h"
#include "Logger.h"

void TileFactory::addTileset(const std::string& tilesetPath, const std::string& imagePath, int firstGid) {
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
        textureMap[i + firstGid] = tileTexture;
        UnloadImage(tileImage);
    }

    UnloadImage(tilesetImageAsImage);
    UnloadTexture(tilesetImage);
}

std::shared_ptr<GameObject> TileFactory::create(int tileId, const std::string& type, Vector2 position) {
    if (textureMap.find(tileId) != textureMap.end()) {
        if (type == "Block") {
            return std::make_shared<Block>(textureMap[tileId], position);
        }
        // else if (type == "Interact") {
        //     return std::make_shared<Interact>(textureMap[tileId], position);
        // }
    }
    return nullptr;
}

MapRenderer::MapRenderer(const std::string& mapPath, std::vector<std::vector<std::shared_ptr<AbstractEntity>>>& mapCollision) { 
    TileFactory factory;
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

    // Load Tilesets
    const std::string dir = "Map/";
    for (const auto& tileset : mapData["tilesets"]) {
        int firstGid = tileset["firstgid"];
        std::string tilesetPath = tileset["source"];
        std::string imagePath = tilesetPath.substr(0, tilesetPath.size() - 5) + ".png";
        factory.addTileset(dir + tilesetPath, dir + imagePath, firstGid);
    }

    for (const auto& layer : mapData["layers"]) {
        if (layer["type"] == "tilelayer") {
            loadLayer(layer, factory);
        } else if (layer["type"] == "objectgroup") {
            // loadObjectGroup(layer, factory);
        }
    }

    // Load mapCollision from objects
    for (const auto& obj : objects) {
        auto position = obj->getComponent<PositionComponent>().getPosition();
        mapCollision[position.x / tileWidth][position.y / tileHeight] = obj;
    }
}

void MapRenderer::loadLayer(const json& layer, TileFactory& factory) {
    int index = 0;
    for (const auto& tileIdValue : layer["data"]) {
        if (!tileIdValue.is_null() && tileIdValue.is_number()) {
            int tileId = tileIdValue.get<int>();
            int x = (index % mapWidth) * tileWidth;
            int y = (index / mapWidth) * tileHeight;
            auto obj = factory.create(tileId, "Block", { (float)x, (float)y });
            if (obj) {
                objects.push_back(obj);
            }
        }
        index++;
    }
}

void MapRenderer::loadObjectGroup(const json& layer, TileFactory& factory) {
    // For object like coins, enemies, special bricks, etc.
}

void MapRenderer::render() {
    for (const auto& obj : objects) {
        obj->draw();
    }
}
