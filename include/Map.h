// #pragma once
// #include "pch.h"
// #include "GameObject.h"
// using json = nlohmann::json;
// // Factory class for creating game objects
// class TileFactory {
//     std::map<int, Texture2D> textureMap;

// public:
//     TileFactory()=default;
//     TileFactory(const std::string& tilesetPath, const std::string& imagePath, const std::string& mapPath);
//     std::shared_ptr<GameObject> Create(int tileId, const std::string& type, Vector2 position);
// };

// // MapRenderer class
// class MapRenderer {
//     std::vector<std::shared_ptr<GameObject>> objects;
//     int mapWidth, mapHeight, tileWidth, tileHeight;

// public:
//     MapRenderer()=default;
//     MapRenderer(const std::string& mapPath, TileFactory& factory);
//     void Render();
// };

// // Camera class
// class MyCamera {
//     Camera2D camera;

// public:
//     MyCamera();
//     void Update(Vector2 target);
//     void BeginMode();
//     void EndMode();
// };
//--------------------FIX--------------------
#pragma once
#include "pch.h"
#include "GameObject.h"
#include "AABB.h"
using json = nlohmann::json;

// Factory class for creating game objects
class TileFactory {
    std::map<int, Texture2D> textureMap;

public:
    TileFactory() = default;
    void addTileset(const std::string& tilesetPath, const std::string& imagePath,int firstgid);
    std::shared_ptr<GameObject> Create(int tileId, const std::string& type, Vector2 position);
};

// MapRenderer class
class MapRenderer {
    std::vector<std::shared_ptr<GameObject>> objects;
    int mapWidth, mapHeight, tileWidth, tileHeight;
    void LoadLayer(const json& layer, TileFactory& factory);
    void LoadObjectGroup(const json& layer, TileFactory& factory);
public:
    MapRenderer() = default;
    MapRenderer(const std::string& mapPath, TileFactory& factory);
    void Render();
};