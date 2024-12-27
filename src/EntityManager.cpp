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
  for (auto &componentArray : componentArrays) {
    componentArray.reset();
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
  ASSERT(id <= lastID, "Destroy invalid entity");
  ComponentIDType lastID = getComponentTypeID(false);
  for (ComponentIDType i = 0; i < lastID; i++) {
    if (componentArrays[i]) {
      componentArrays[i]->onEntityDestroyed(id);
    }
  }

  entities[id]->deactivate();
  entities[id].reset();
  entities[id] = nullptr;
  bitsetEntityMap[entityBitsetMap[id]].erase(id);
  entityBitsetMap.erase(id);
}

void EntityManager::destroyEntity(std::string name) {
#ifdef _DEBUG
  Log("Destroying multiple entities with name: " + name, LogLevel::WARNING);
#endif
  auto entities = getEntityByName(name);
  for (auto &entity : entities) {
    ASSERT(entity.expired(), "Destroy invalid entity");
    destroyEntity(entity.lock()->getID());
  }
}

void EntityManager::destroyEntity(AbstractEntity &entity) {
  destroyEntity(entity.getID());
}

void EntityManager::destroyEntity(Weak<AbstractEntity> entity) {
  ASSERT(!entity.expired(), "Destroy invalid entity");
  destroyEntity(entity.lock()->getID());
}

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
void AbstractEntity::deactivate() { active = false; }
void AbstractEntity::destroy() {
  active = false;
  EM->destroyEntity(id);
}

std::string AbstractEntity::getName() const { return name; }
void AbstractEntity::setName(std::string name) { this->name = name; }

void to_json(json &j, const EntityManager &entity) {
  for (auto &e : entity.entities) {
    if (e) {
      j["entities"].push_back(*e);
    }
  }

  for (auto &[k, v] : entity.entityBitsetMap) {
    j["entityBitsetMap"][k] = v.to_string();
  }

  for (auto &[k, v] : entity.bitsetEntityMap) {
    j["bitsetEntityMap"][k.to_string()] =
        std::vector<EntityID>(v.begin(), v.end());
  }

  for (auto &[k, v] : entity.entityNameMap) {
    j["entityNameMap"][k] = std::vector<EntityID>(v.begin(), v.end());
  }
}

// void from_json(const json &j, EntityManager &entity) {
//   for (auto &e : j["entities"]) {
//     EntityID id = e.at("id").get<EntityID>();
//     std::string name = e.at("name").get<std::string>();
//     bool acitve = e.at("active").get<bool>();
//   }
// }

void EntityManager::accept(IExporter &e) { e.visit(*this); }
