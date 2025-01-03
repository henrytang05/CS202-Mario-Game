#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Exporter.h"
#include "Interface.h"
#include "globals.h"
#include <bitset>
#include <unordered_map>
#include <unordered_set>

#define UNNAMED "Unnamed"
#define INVALID_ENTITY_ID -1

class Component;
class EntityManager;
// NOTE: Component
typedef uint32_t EntityID;
constexpr std::size_t maxComponents = 64;
constexpr std::size_t maxEntity = 1024;
using ComponentIDType = uint32_t;

inline ComponentIDType getComponentTypeID(bool next = true) {
  static ComponentIDType lastID = 0;
  if (next)
    return lastID++;
  else
    return lastID;
}

template <typename T> inline ComponentIDType getComponentTypeID() noexcept {
  static ComponentIDType typeID = getComponentTypeID();
  return typeID;
}

class IComponentArray {
public:
  virtual ~IComponentArray() = default;
  virtual void onEntityDestroyed(EntityID id) = 0;
  std::string getName() const { return name; }
  void setName(std::string name) { this->name = name; }

  virtual void to_json(json &j) const = 0;
  std::string name;
};

template <typename T> class ComponentArray : public IComponentArray {
public:
  ComponentArray<T>() { entityComponentIndexMap.fill(-1); }
  virtual ~ComponentArray() = default;

  void to_json(json &j) const override {
    for (auto &c : components) {
      json j97;
      c.to_json(j97);
      j["components"].push_back(j97);
    }
    j["entityComponentIndexMap"] = entityComponentIndexMap;
  }
  void onEntityDestroyed(EntityID id) override {
    if (entityComponentIndexMap[id] == -1)
      return;

    if (entityComponentIndexMap[id] != -1) {
      size_t index = entityComponentIndexMap[id];
      auto &ECIM = entityComponentIndexMap;
      components[index] = std::move(components.back());

      for (size_t i = 0; i < ECIM.size(); i++) {
        if (ECIM[i] != (int)components.size() - 1)
          continue;
        ECIM[i] = index;
        break;
      }

      components.pop_back();
      entityComponentIndexMap[id] = -1;
    }
  }

  std::vector<T> components;
  std::array<ComponentIDType, maxEntity>
      entityComponentIndexMap; // entityID : componentIndex
};

class AbstractEntity : public IUpdatable {

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(AbstractEntity, id, name, active)
private:
  bool active;       // check if entity is active
  uint32_t id;       // entity id
  std::string name;  // name for debuggin
  EntityManager *EM; // Haven't find a way to make this safer

public:
  AbstractEntity() = default; // Avoid using this constructor
                              // this is a temporary solution
  AbstractEntity(EntityManager &EM, uint32_t id = INVALID_ENTITY_ID,
                 std::string name = UNNAMED, bool active = true);

  AbstractEntity(std::string name = UNNAMED, uint32_t id = INVALID_ENTITY_ID,
                 bool active = true);

  virtual ~AbstractEntity();

  void initEntity();
  uint32_t getID() const;
  bool operator==(const AbstractEntity &other) const;
  bool operator!=(const AbstractEntity &other) const;

  bool isActive() const;
  void deactivate();
  void destroy();

  virtual void update(float deltaTime) override;
  virtual void changeState();

  // WARNING: This is a temporary solution
  std::string getName() const;
  void setName(std::string name);

  template <typename T> inline bool hasComponent() const;

  template <typename... TArgs> inline bool hasAllComponents() const;

  template <typename T, typename... TArgs>
  inline T &addComponent(TArgs &&...mArgs);

  template <typename T> inline T &getComponent();

  template <typename T> inline void removeComponent();

  template <typename T, typename... TArgs>
  inline T &modifyComponent(TArgs &&...mArgs);
};

class EntityManager : public IExportable {

public:
  friend void to_json(json &j, const EntityManager &entity);
  friend void from_json(const json &j, EntityManager &entity);
  void accept(IVisitor &e) override;

private:
  inline static EntityID lastID = 0;
  std::array<Shared<AbstractEntity>, maxEntity>
      entities; // id : entity
                // TODO: change ptr type later
  std::array<Shared<IComponentArray>, maxComponents>
      componentArrays; // componentIDType : componentArray

  std::unordered_map<std::bitset<maxComponents>, std::unordered_set<EntityID>>
      bitsetEntityMap; // component bitset : entities with those components
  std::unordered_map<EntityID, std::bitset<maxComponents>> entityBitsetMap;

  std::unordered_map<std::string, std::unordered_set<EntityID>> entityNameMap;

public:
  Weak<AbstractEntity> createEntity(std::string name = UNNAMED);
  std::array<Shared<AbstractEntity>, maxEntity> &getAllEntities();
  std::vector<Weak<AbstractEntity>> getEntities();

  AbstractEntity &getEntityRef(uint32_t id);
  Weak<AbstractEntity> getEntityPtr(uint32_t id);

  std::vector<Weak<AbstractEntity>> getEntityByName(std::string name);

  std::vector<EntityID> getEntityID(std::string name);
  uint32_t getEntityID(AbstractEntity &entity);
  uint32_t getEntityID(Weak<AbstractEntity> entity);
  uint32_t getEntityID(Shared<AbstractEntity> &entity);

  std::bitset<maxComponents> getEntityBitset(AbstractEntity &entity);
  void destroyEntity(uint32_t id);
  void destroyEntity(std::string name);
  void destroyEntity(AbstractEntity &entity);
  void destroyEntity(Weak<AbstractEntity> entity);
  uint32_t nextID(bool reset = false) const;

  template <typename T>
  inline bool hasComponent(const AbstractEntity *entity) const;

  template <typename T>
  inline bool hasComponent(Shared<AbstractEntity> entity) const;

  template <typename... TArgs>
  inline bool hasAllComponents(const AbstractEntity *entity) const;

  template <typename... TArgs>
  inline bool hasAllComponents(Shared<AbstractEntity> entity) const;

  template <typename T, typename... TArgs>
  inline T &addComponent(AbstractEntity *entity, TArgs &&...mArgs);

  template <typename T, typename... TArgs>
  inline T &addComponent(Shared<AbstractEntity> entity, TArgs &&...mArgs);

  template <typename T> inline T &getComponent(AbstractEntity *entity);
  template <typename T> inline T &getComponent(Shared<AbstractEntity> entity);

  template <typename... TArgs>
  inline std::vector<Weak<AbstractEntity>> getHasAll();

  template <typename T> inline ComponentArray<T> *getComponentsArray();

  template <typename T> inline void removeComponent(AbstractEntity *entity);
  template <typename T>
  inline void removeComponent(Shared<AbstractEntity> entity);

  template <typename T, typename... TArgs>
  inline T &modifyComponent(AbstractEntity *entity, TArgs &&...mArgs);
  template <typename T, typename... TArgs>
  inline T &modifyComponent(Shared<AbstractEntity> entity, TArgs &&...mArgs);

  void reset();
  static EntityManager &getInstance();
  ~EntityManager();

  EntityManager();

private:
  EntityManager(const EntityManager &) = delete;
  EntityManager &operator=(const EntityManager &) = delete;
};

template <typename T>
inline bool EntityManager::hasComponent(const AbstractEntity *entity) const {
  ASSERT(entity->getID() <= lastID, "Invalid entity ID in hasComponent");
  return entityBitsetMap.at(entity->getID())[getComponentTypeID<T>()];
}

template <typename T>
inline bool EntityManager::hasComponent(Shared<AbstractEntity> entity) const {
  return hasComponent<T>(entity.get());
}

template <typename T, typename... TArgs>
inline T &EntityManager::addComponent(AbstractEntity *entity,
                                      TArgs &&...mArgs) {

  ASSERT(entity->getID() <= lastID, "Invalid entity ID in addComponent");
  if (hasComponent<T>(entity)) {
    throw std::runtime_error("Entity already has component");
  }

  auto &bitset = entityBitsetMap[entity->getID()];

  EntityID eid = entity->getID();

  // remove from old bitsetEntityMap
  bitsetEntityMap[bitset].erase(eid);

  // add to new bitsetEntityMap
  bitset[getComponentTypeID<T>()] = true;
  bitsetEntityMap[bitset].insert(eid);
  entityBitsetMap[eid] = bitset;

  // add to component array
  ComponentArray<T> &componentsArr = *getComponentsArray<T>();
  std::vector<T> &components = componentsArr.components;
  components.emplace_back(std::forward<TArgs>(mArgs)...);
  components.back().setEntity(entity);
  components.back().setEntityManager(this);

  size_t index = componentsArr.components.size() - 1;
  std::array<ComponentIDType, maxEntity> &ECM =
      componentsArr.entityComponentIndexMap;
  ECM[eid] = index;

  T &ret = componentsArr.components.at(index);
  return ret;
}

template <typename T, typename... TArgs>
inline T &EntityManager::addComponent(Shared<AbstractEntity> entity,
                                      TArgs &&...mArgs) {
  return addComponent<T>(entity.get(), std::forward<TArgs>(mArgs)...);
}

template <typename... TArgs>
inline bool
EntityManager::hasAllComponents(const AbstractEntity *entity) const {
  return (hasComponent<TArgs>(entity) && ...);
}

template <typename... TArgs>
inline bool
EntityManager::hasAllComponents(Shared<AbstractEntity> entity) const {
  return (hasComponent<TArgs>(entity.get()) && ...);
}

template <typename T>
inline T &EntityManager::getComponent(AbstractEntity *entity) {
  ASSERT(entity->getID() <= lastID, "Invalid entity ID in removeComponent");
  if (!hasComponent<T>(entity)) {
    throw std::runtime_error("Entity does not have component");
  }

  auto componentsArr = getComponentsArray<T>();
  auto index = componentsArr->entityComponentIndexMap[entity->getID()];
  if (index == -1) {
    throw std::runtime_error("Entity does not have component");
  }
  return componentsArr->components.at(index);
}

template <typename T>
inline T &EntityManager::getComponent(Shared<AbstractEntity> entity) {
  return getComponent<T>(entity.get());
}

template <typename T>
inline void EntityManager::removeComponent(AbstractEntity *entity) {
  if (!hasComponent<T>(entity)) {
    throw std::runtime_error("Entity does not have component");
  }

  EntityID eid = entity->getID();
  auto &bitset = entityBitsetMap[eid];
  auto &bs = bitsetEntityMap[bitset];
  bs.erase(eid);

  bitset[getComponentTypeID<T>()] = false;
  bitsetEntityMap[bitset].insert(eid);
  entityBitsetMap[eid] = bitset;

  ComponentArray<T> &componentsArr = *getComponentsArray<T>();
  std::vector<T> &components = componentsArr.components;
  size_t index = componentsArr.entityComponentIndexMap[eid];
  auto &ECIM = componentsArr.entityComponentIndexMap;
  componentsArr.components[index] = std::move(components.back());

  for (size_t i = 0; i < ECIM.size(); i++) {
    if (ECIM[i] != (int)components.size() - 1)
      continue;
    ECIM[i] = index;
    break;
  }

  components.pop_back();
  componentsArr.entityComponentIndexMap[eid] = -1;
}
template <typename T>
inline void EntityManager::removeComponent(Shared<AbstractEntity> entity) {
  removeComponent<T>(entity.get());
}
template <typename T, typename... TArgs>
inline T &EntityManager::modifyComponent(AbstractEntity *entity,
                                         TArgs &&...mArgs) {
  if (!hasComponent<T>(entity)) {
    throw std::runtime_error("Entity does not have component");
  }

  ComponentArray<T> &componentsArr = *getComponentsArray<T>();
  auto &ECM = componentsArr.entityComponentIndexMap;
  auto index = ECM[entity->getID()];
  if (index == -1) {
    throw std::runtime_error("Entity does not have component");
  }

  componentsArr.components[index] = T(std::forward<TArgs>(mArgs)...);

  std::vector<T> &components = componentsArr.components;
  components[index].setEntity(entity);
  components[index].setEntityManager(this);

  T &ret = componentsArr.components[index];
  ret.setEntity(entity);
  ret.setEntityManager(this);
  return ret;
}

template <typename T, typename... TArgs>
inline T &EntityManager::modifyComponent(Shared<AbstractEntity> entity,
                                         TArgs &&...mArgs) {
  return modifyComponent<T>(entity.get(), std::forward<TArgs>(mArgs)...);
}

template <typename T>
inline ComponentArray<T> *EntityManager::getComponentsArray() {
  auto it = componentArrays[getComponentTypeID<T>()];
  if (!it) {
    // create new
    auto componentArray = std::make_shared<ComponentArray<T>>();
    componentArray->setName(typeid(T).name());
    componentArrays[getComponentTypeID<T>()] = std::move(componentArray);
  }

  // Safely cast the IComponentArray to ComponentArray<T>
  ComponentIDType CTypeID = getComponentTypeID<T>();
  IComponentArray *ica = componentArrays[CTypeID].get();
  auto componentArray = static_cast<ComponentArray<T> *>(ica);
  if (!componentArray) {
    throw std::runtime_error("Invalid component array cast for type T");
  }

  return componentArray;
}

template <typename... TArgs>
inline std::vector<Weak<AbstractEntity>> EntityManager::getHasAll() {
  std::bitset<maxComponents> bitset;
  (bitset.set(getComponentTypeID<TArgs>()), ...);

  std::vector<Weak<AbstractEntity>> ret;

  for (auto &[k, v] : bitsetEntityMap) {
    if ((k & bitset) == bitset) {
      for (auto &id : v) {
        ret.push_back(getEntityPtr(id));
      }
    }
  }

  return ret;
}

template <typename T> inline bool AbstractEntity::hasComponent() const {
  return EM->hasComponent<T>(this);
}

template <typename... TArgs>
inline bool AbstractEntity::hasAllComponents() const {
  return EM->hasAllComponents<TArgs...>(this);
}

template <typename T, typename... TArgs>
inline T &AbstractEntity::addComponent(TArgs &&...mArgs) {
  return EM->addComponent<T>(this, std::forward<TArgs>(mArgs)...);
}

template <typename T> inline T &AbstractEntity::getComponent() {
  return EM->getComponent<T>(this);
}

template <typename T> inline void AbstractEntity::removeComponent() {
  EM->removeComponent<T>(this);
}

template <typename T, typename... TArgs>
inline T &AbstractEntity::modifyComponent(TArgs &&...mArgs) {
  return EM->modifyComponent<T>(this, std::forward<TArgs>(mArgs)...);
}

void to_json(json &j, const EntityManager &entity);
void from_json(const json &j, EntityManager &entity);

#endif // ENTITY_MANAGER_H
