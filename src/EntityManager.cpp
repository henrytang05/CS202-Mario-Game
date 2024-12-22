#include "EntityManager.h"
#include "Components/Component.h"
#include <bitset>
#include <sys/types.h>

EntityManager::EntityManager() {}
EntityManager::~EntityManager() {}

EntityManager &EntityManager::get() {
  static EntityManager instance;
  return instance;
}

std::vector<Unique<AbstractEntity>> &EntityManager::getEntities() {
  return entities;
}

uint32_t EntityManager::nextID() const {
  static uint32_t id = 0;
  return id++;
}

uint32_t EntityManager::getEntityID(std::string name) {
  return entityNameMap[name]->getID();
}

uint32_t EntityManager::getEntityID(AbstractEntity &entity) {
  return entity.getID();
}

AbstractEntity &EntityManager::createEntity(std::string name) {
  uint32_t id = nextID();
  Unique<AbstractEntity> entity = std::make_unique<AbstractEntity>(id, name);

  auto bitset = getEntityBitset(*entity);
  entities.push_back(std::move(entity));
  bitsetEntityMap[bitset].push_back(entities.back().get());
  entityNameMap[name] = entities.back().get();

  return *entities.back().get();
}

AbstractEntity &EntityManager::getEntity(uint32_t id) {
  for (auto &entity : entities) {
    if (entity->getID() == id) {
      return *entity.get();
    }
  }
  throw std::runtime_error("Entity not found");
}

AbstractEntity &EntityManager::getEntity(std::string name) {
  if (entityNameMap.find(name) != entityNameMap.end()) {
    return *entityNameMap[name];
  }
  throw std::runtime_error("Entity not found");
}

std::bitset<maxComponents>
EntityManager::getEntityBitset(AbstractEntity &entity) {
  return entityBitsetMap[entity.getID()];
}

void EntityManager::destroyEntity(uint32_t id) {
  throw std::runtime_error("Not implemented");
}

void EntityManager::destroyEntity(std::string name) {
  throw std::runtime_error("Not implemented");
}
