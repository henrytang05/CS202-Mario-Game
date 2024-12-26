#pragma once
#include "Components/BoundingBox.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Entity/EntityFactory.h"
#include "EntityManager.h"
#include "TextureManager.h"
using json = nlohmann::json;

// MapRenderer class
class MapRenderer {
private:
  std::vector<Weak<AbstractEntity>> objects;
  int mapWidth, mapHeight, tileWidth, tileHeight;
  Unique<IFactory> entityFactory;
  EntityManager &EM = EntityManager::getInstance();

public:
  void loadObjectGroup(const json &layer);
  MapRenderer() = default;
  std::vector<Weak<AbstractEntity>> createMap(const std::string &mapPath);
  void render();
};
