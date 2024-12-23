#include "EntityManager.h"
#include "pch.h"

template <typename T> ComponentArray<T>::~ComponentArray() {
  // components.clear();
  // entityComponentIndexMap.clear();
}

EntityManager::EntityManager() {}
EntityManager::~EntityManager() {
  std::cout << "Cleaning up EntityManager" << std::endl;
}

std::array<Shared<AbstractEntity>, maxEntity> &EntityManager::getEntities() {
  return entities;
}

uint32_t EntityManager::nextID() const {
  static uint32_t id = 0;
  return id++;
}

uint32_t EntityManager::getEntityID(std::string name) {
  return entityNameMap[name];
}

uint32_t EntityManager::getEntityID(AbstractEntity &entity) {
  return entity.getID();
}

uint32_t EntityManager::getEntityID(Weak<AbstractEntity> entity) {
  return entity.lock()->getID();
}

uint32_t EntityManager::getEntityID(Shared<AbstractEntity> &entity) {
  return entity->getID();
}

Weak<AbstractEntity> EntityManager::createEntity(std::string name) {
  if (entityNameMap.count(name)) {
    throw std::runtime_error("Entity with name already exists");
  }
  uint32_t id = nextID();
  Shared<AbstractEntity> entity =
      std::make_shared<AbstractEntity>(*this, id, name);

  std::bitset<maxComponents> bitset = getEntityBitset(*entity);
  entities[id] = entity;
  entityBitsetMap[id] = bitset;
  bitsetEntityMap[bitset].insert(id);

  entityNameMap[name] = id;

  return entities[id];
}

AbstractEntity &EntityManager::getEntityRef(uint32_t id) {
  if (entities[id]) {
    return *entities[id].get();
  }
  throw std::runtime_error("Entity not found");
}

AbstractEntity &EntityManager::getEntityRef(std::string name) {
  if (entityNameMap.count(name)) {
    std::cout << "Entity found\n";
    std::cout << entityNameMap[name] << std::endl;
    return *entities[entityNameMap[name]].get();
  }
  throw std::runtime_error("Entity not found");
}

Weak<AbstractEntity> EntityManager::getEntityPtr(std::string name) {
  if (entities[entityNameMap[name]]) {
    return entities[entityNameMap[name]];
  }
  throw std::runtime_error("Entity not found");
}

Weak<AbstractEntity> EntityManager::getEntityPtr(uint32_t id) {
  if (entities[id]) {
    return entities[id];
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

void EntityManager::destroyEntity(AbstractEntity &entity) {
  throw std::runtime_error("Not implemented");
}

void EntityManager::destroyEntity(Weak<AbstractEntity> entity) {
  throw std::runtime_error("Not implemented");
}

// AbstractEntity::AbstractEntity() : active(false), id(INVALID_ENTITY_ID),
// name(UNNAMED), EM(nullptr) {}

AbstractEntity::AbstractEntity(EntityManager &EM, uint32_t id, std::string name,
                               bool active)
    : active(active), id(id), name(name), EM(EM) {}

bool AbstractEntity::operator==(const AbstractEntity &other) const {
  return id == other.id;
}

bool AbstractEntity::operator!=(const AbstractEntity &other) const {
  return id != other.id;
}

AbstractEntity::~AbstractEntity() {
#ifdef _DEBUG
  Log(name + " created: " + std::to_string(id));
#endif
}

uint32_t AbstractEntity::getID() const { return id; }

bool AbstractEntity::isActive() const { return active; }

void AbstractEntity::destroy() {
  active = false;
  EM.destroyEntity(id);
}

std::string AbstractEntity::getName() const { return name; }
