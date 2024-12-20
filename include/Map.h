#pragma once
#include "pch.h"
#include "GameObject.h"
#include "Components/BoundingBox.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Entity/EntityFactory.h"
#include "TextureManager.h"
using json = nlohmann::json;

// MapRenderer class
class MapRenderer {
private:
    std::vector<std::shared_ptr<AbstractEntity>> objects;
    int mapWidth, mapHeight, tileWidth, tileHeight;
    Unique<IFactory> entityFactory;

public:
    void loadObjectGroup(const json& layer);
    MapRenderer() = default;
    std::vector<Shared<AbstractEntity>> createMap(const std::string& mapPath);
    void render();
};
