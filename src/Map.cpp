#include "Map.h"

// void Block::Render() {
//     DrawTexture(texture, position.x, position.y, WHITE);
// }

// void Interact::Render() {
//     DrawTexture(texture, position.x, position.y, WHITE);
// }

TileFactory::TileFactory(const std::string &tilesetPath,
                         const std::string &imagePath) {
  std::ifstream file(tilesetPath);
  json tilesetData;
  file >> tilesetData;

  Texture2D tilesetImage = LoadTexture(imagePath.c_str());
  Image tilesetImageAsImage = LoadImageFromTexture(tilesetImage);

  int tileWidth = tilesetData["tilewidth"];
  int tileHeight = tilesetData["tileheight"];
  int columns = tilesetData["columns"];
  int tileCount = tilesetData["tilecount"];

  for (int i = 0; i < tileCount; ++i) {
    float x = (i % columns) * tileWidth;
    float y = (i / columns) * tileHeight;
    Image tileImage = ImageFromImage(
        tilesetImageAsImage, {x, y, (float)tileWidth, (float)tileHeight});
    Texture2D tileTexture = LoadTextureFromImage(tileImage);
    textureMap[i] = tileTexture;
    UnloadImage(tileImage);
  }

  UnloadImage(tilesetImageAsImage);
  UnloadTexture(tilesetImage);
}

std::shared_ptr<GameObject>
TileFactory::Create(int tileId, const std::string &type, Vector2 position) {
  if (textureMap.find(tileId) != textureMap.end()) {
    if (type == "Block") {
      return std::make_shared<Block>(textureMap[tileId], position);
    } else if (type == "Interact") {
      return std::make_shared<Interact>(textureMap[tileId], position);
    }
  }
  return nullptr;
}

MapRenderer::MapRenderer(const std::string &mapPath, TileFactory &factory) {
  std::ifstream file(mapPath);
  json mapData;
  file >> mapData;

  mapWidth = mapData["width"];
  mapHeight = mapData["height"];
  tileWidth = mapData["tilewidth"];
  tileHeight = mapData["tileheight"];

  int groundLevel = (3 * 810) / 4;

  for (const auto &layer : mapData["layers"]) {
    if (layer["type"] == "tilelayer") {
      int index = 0;
      for (const auto &tileIdValue : layer["data"]) {
        if (!tileIdValue.is_null() && tileIdValue.is_number()) {
          int tileId = tileIdValue.get<int>();
          if (mapData.contains("tilesets") && !mapData["tilesets"].empty()) {
            int firstgid = mapData["tilesets"][0]["firstgid"].get<int>();
            if (tileId >= firstgid) {
              int x = (index % mapWidth) * tileWidth;
              int y = (index / mapWidth) * tileHeight;
              std::cerr << "y: " << y << std::endl;
              std::cerr << "index: " << index << std::endl;
              int offset = tileId - firstgid;
              auto obj = factory.Create(offset, "Block", {(float)x, (float)y});
              if (obj) {
                objects.push_back(obj);
              }
            }
          }
        }
        index++;
      }
    }
  }
}

void MapRenderer::Render() {
  for (const auto &obj : objects) {
    obj->Render();
  }
}

// #include "Map.h"

// Block rendering
// void Block::Render() {
//     DrawTexture(texture, position.x, position.y, WHITE);
// }

// Interact rendering
// void Interact::Render() {
//     DrawTexture(texture, position.x, position.y, WHITE);
// }

// TileFactory constructor
// TileFactory::TileFactory(const std::string& tilesetPath, const std::string&
// imagePath, b2World& world)
//     : world(world) {
//     std::ifstream file(tilesetPath);
//     json tilesetData;
//     file >> tilesetData;

//     Texture2D tilesetImage = LoadTexture(imagePath.c_str());
//     Image tilesetImageAsImage = LoadImageFromTexture(tilesetImage);

//     tileWidth = tilesetData["tilewidth"];
//     tileHeight = tilesetData["tileheight"];
//     int columns = tilesetData["columns"];
//     int tileCount = tilesetData["tilecount"];

//     Create default tiles
//     for (int i = 0; i < tileCount; ++i) {
//         float x = (i % columns) * tileWidth;
//         float y = (i / columns) * tileHeight;

//         Image tileImage = ImageFromImage(tilesetImageAsImage, { x, y,
//         (float)tileWidth, (float)tileHeight }); Texture2D tileTexture =
//         LoadTextureFromImage(tileImage);

//         tileMap[i] = std::make_shared<Tile>(tileTexture, "default", false);

//         UnloadImage(tileImage);
//     }

//     Update tiles based on JSON
//     for (const auto& tile : tilesetData["tiles"]) {
//         int id = tile["id"];
//         std::string type = tile.contains("type") ?
//         tile["type"].get<std::string>() : "default"; bool collision =
//         tile.contains("objectgroup") &&
//         !tile["objectgroup"]["objects"].empty();

//         if (tileMap.find(id) != tileMap.end()) {
//             tileMap[id]->type = type;
//             tileMap[id]->collision = collision;
//         }
//     }

//     UnloadImage(tilesetImageAsImage);
//     UnloadTexture(tilesetImage);
// }

// Create game objects
// std::shared_ptr<GameObject> TileFactory::Create(int tileId, Vector2 position)
// {
//     auto tile = tileMap.find(tileId);
//     if (tile != tileMap.end()) {
//         auto& tileData = tile->second;

//         Correct usage of AABB creation
//         if (tileData->collision) {
//             Vector2 size= { (float)tileWidth, (float)tileHeight };
//             tileData->aabb = std::make_unique<AABB>(world, position, size);
//         }

//         if (tileData->type == "Block") {
//             return std::make_shared<Block>(tileData->texture, position);
//         } else if (tileData->type == "Interact") {
//             return std::make_shared<Interact>(tileData->texture, position);
//         }
//     }
//     return nullptr;
// }

// MapRenderer constructor
// MapRenderer::MapRenderer(const std::string& mapPath, TileFactory& factory)
//     : factory(factory) {
//     std::ifstream file(mapPath);
//     json mapData;
//     file >> mapData;

//     mapWidth = mapData["width"];
//     mapHeight = mapData["height"];
//     tileWidth = mapData["tilewidth"];
//     tileHeight = mapData["tileheight"];

//     for (const auto& layer : mapData["layers"]) {
//         if (layer["type"] == "tilelayer") {
//             int index = 0;
//             for (const auto& tileIdValue : layer["data"]) {
//                 if (!tileIdValue.is_null() && tileIdValue.is_number()) {
//                     int tileId = tileIdValue.get<int>();
//                     int x = (index % mapWidth) * tileWidth;
//                     int y = (index / mapWidth) * tileHeight;
//                     auto obj = factory.Create(tileId, { (float)x, (float)y
//                     }); if (obj) {
//                         objects.push_back(obj);
//                     }
//                 }
//                 index++;
//             }
//         }
//     }
// }

// Render map
// void MapRenderer::Render() {
//     for (const auto& obj : objects) {
//         obj->Render();
//     }

//     Debug collision boundaries
//     for (const auto& tile : factory.GetTileMap()) {
//         if (tile.second->collision && tile.second->aabb) {
//             Vector2 pos = tile.second->aabb->GetPosition();
//             DrawRectangleLines(pos.x, pos.y, tileWidth, tileHeight, RED);
//         }
//     }
// }
