#pragma once
#include "pch.h"
#include "GameObject.h"
#include "Components/BoundingBox.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Entity/EntityFactory.h"
using json = nlohmann::json;


// MapRenderer class
class MapRenderer {
private:
    map<int, pair<string,Texture2D>> textureMap;
    std::vector<std::shared_ptr<Block>> objects;
    int mapWidth, mapHeight, tileWidth, tileHeight;
    Unique<IFactory> entityFactory;

public:
    void addTileset(const std::string& tilesetPath, const std::string& imagePath, int firstGid);
    void loadLayer(const json& layer);
    void loadObjectGroup(const json& layer);
    MapRenderer() = default;
    std::vector<Shared<Block>> createMap(const std::string& mapPath);
    void render();
};
