#include "EntityManager.h"
#include "Logger.h"
#include "pch.h"

EntityManager &EntityManager::getInstance() {
  static EntityManager EM;
  return EM;
}

void EntityManager::reset() {
  entityNameMap.clear();
  entityBitsetMap.clear();
  bitsetEntityMap.clear();
  nextID(true);
  for (auto &entity : entities) {
    entity.reset();
  }
}

EntityManager::EntityManager() {}
EntityManager::~EntityManager() {
  std::cout << "Cleaning up EntityManager" << std::endl;
}

std::array<Shared<AbstractEntity>, maxEntity> &EntityManager::getAllEntities() {
  return entities;
}

std::vector<Weak<AbstractEntity>> EntityManager::getEntities() {
  std::vector<Weak<AbstractEntity>> res;
  for (auto &entity : entities) {
    if (entity) {
      res.push_back(entity);
    }
  }
  return res;
}

uint32_t EntityManager::nextID(bool reset) const {
  static uint32_t id = 0;
  if (reset) {
    id = 0;
  }
  EntityManager::lastID = id;
  return id++;
}

std::vector<EntityID> EntityManager::getEntityID(std::string name) {
  if (entityNameMap.count(name)) {
    std::vector<EntityID> res(entityNameMap[name].begin(),
                              entityNameMap[name].end());
    return res;
  }
  throw std::runtime_error("Entity not found");
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
  uint32_t id = nextID();
  Shared<AbstractEntity> entity =
      std::make_shared<AbstractEntity>(*this, id, name);

  std::bitset<maxComponents> bitset = getEntityBitset(*entity);
  entities[id] = entity;
  entityBitsetMap[id] = bitset;
  bitsetEntityMap[bitset].insert(id);

  entityNameMap[name].insert(id);

  return entities[id];
}

AbstractEntity &EntityManager::getEntityRef(uint32_t id) {
  if (entities[id]) {
    return *entities[id].get();
  }
  throw std::runtime_error("Entity not found");
}

std::vector<Weak<AbstractEntity>>
EntityManager::getEntityByName(std::string name) {
  if (entityNameMap.count(name)) {
    std::vector<Weak<AbstractEntity>> res;
    std::transform(entityNameMap[name].begin(), entityNameMap[name].end(),
                   std::back_inserter(res),
                   [&](auto id) { return entities[id]; });
    return res;
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
    : active(active), id(id), name(name), EM(&EM) {}

AbstractEntity::AbstractEntity(std::string name, uint32_t id, bool active)
    : active(active), id(id), name(name), EM(nullptr) {}

void AbstractEntity::update(float deltaTime) {}
void AbstractEntity::changeState() {}

void AbstractEntity::initEntity() {
  auto &EM = EntityManager::getInstance();
  *this = *EM.createEntity(name).lock().get();
}

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
  EM->destroyEntity(id);
}

std::string AbstractEntity::getName() const { return name; }
void AbstractEntity::setName(std::string name) { this->name = name; }
