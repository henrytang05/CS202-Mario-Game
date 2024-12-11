#pragma once
#include "pch.h"
#include "GameObject.h"
#include "Components/BoundingBox.h"
#include "Components/Position.h"
#include "Components/Texture.h"
using json = nlohmann::json;

// Factory class for creating game objects
class TileFactory {
    std::map<int, Texture2D> textureMap;

public:
    TileFactory() = default;
    void addTileset(const std::string& tilesetPath, const std::string& imagePath, int firstGid);
    std::shared_ptr<GameObject> create(int tileId, const std::string& type, Vector2 position);
};

// MapRenderer class
class MapRenderer {
private:
    std::vector<std::shared_ptr<GameObject>> objects;
    int mapWidth, mapHeight, tileWidth, tileHeight;

public:
    void loadLayer(const json& layer, TileFactory& factory);
    void loadObjectGroup(const json& layer, TileFactory& factory);
    MapRenderer() = default;
    MapRenderer(const std::string& mapPath, std::vector<std::vector<std::shared_ptr<AbstractEntity>>>& mapCollision);
    void render();
};