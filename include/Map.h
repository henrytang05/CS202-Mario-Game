#pragma once
#include "pch.h"
#include "GameObject.h"
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

// #pragma once
// #include "GameObject.h"
// #include "pch.h"
// using json = nlohmann::json;

// // Factory class for creating game objects
// class TileFactory {
//   std::map<int, Texture2D> textureMap;

// public:
//   TileFactory() = default;
//   TileFactory(const std::string &tilesetPath, const std::string &imagePath);
//   std::shared_ptr<GameObject> Create(int tileId, const std::string &type,
//                                      Vector2 position);
// };

// // MapRenderer class
// class MapRenderer {
//   std::vector<std::shared_ptr<GameObject>> objects;
//   int mapWidth, mapHeight, tileWidth, tileHeight;

// public:
//   MapRenderer() = default;
//   MapRenderer(const std::string &mapPath, TileFactory &factory);
//   void Render();
// };

// // #pragma once
// // #include "AABB.h"
// // #include "pch.h"

// // using json = nlohmann::json;

// // // Base class for all objects
// // class GameObject {
// // protected:
// //     Vector2 position;

// // public:
// //     GameObject(Vector2 pos) : position(pos) {}
// //     virtual void Render() = 0;
// //     void SetPosition(Vector2 pos) { position = pos; }
// //     Vector2 GetPosition() const { return position; }
// // };

// // // Tile class to store texture and metadata
// // class Tile {
// // public:
// //     Texture2D texture;
// //     std::string type;
// //     bool collision;
// //     std::unique_ptr<AABB> aabb;

// //     Tile(Texture2D tex, const std::string& type, bool collision)
// //         : texture(tex), type(type), collision(collision), aabb(nullptr) {}
// // };

// // // Derived class for a block
// // class Block : public GameObject {
// //     Texture2D texture;

// // public:
// //     Block(Texture2D tex, Vector2 pos) : GameObject(pos), texture(tex) {}
// //     void Render() override;
// // };

// // // Derived class for an interactable object
// // class Interact : public GameObject {
// //     Texture2D texture;

// // public:
// //     Interact(Texture2D tex, Vector2 pos) : GameObject(pos), texture(tex) {}
// //     void Render() override;
// // };

// // // Factory class for creating game objects
// // class TileFactory {
// // private:
// //     std::map<int, std::shared_ptr<Tile>> tileMap;
// //     b2World& world;
// //     int tileWidth, tileHeight;

// // public:
// //     TileFactory(const std::string& tilesetPath, const std::string& imagePath,
// //     b2World& world); std::shared_ptr<GameObject> Create(int tileId, Vector2
// //     position);

// //     // Getter for tileMap to avoid access issues
// //     std::map<int, std::shared_ptr<Tile>>& GetTileMap() { return tileMap; }
// // };

// // // MapRenderer class
// // class MapRenderer {
// //     std::vector<std::shared_ptr<GameObject>> objects;
// //     TileFactory& factory;
// //     int mapWidth, mapHeight, tileWidth, tileHeight;

// // public:
// //     MapRenderer(const std::string& mapPath, TileFactory& factory);
// //     void Render();
// // };
