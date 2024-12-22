#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "AbstractEntity.h"
#include "pch.h"
#include <bitset>
#include <unordered_map>

#define UNNAMED "Unnamed"

typedef uint32_t EntityID;
constexpr std::size_t maxComponents = 64;
using ComponentTypeID = std::size_t;

inline ComponentTypeID getComponentTypeID() {
  static ComponentTypeID lastID = 0;
  return lastID++;
}

template <typename T> inline ComponentTypeID getComponentTypeID() noexcept {
  static ComponentTypeID typeID = getComponentTypeID();
  return typeID;
}
class IComponentArray {
public:
  virtual ~IComponentArray() = default;
  virtual void onEntityDestroyed(EntityID id) = 0;
};

class EntityManager {
  typedef uint32_t EntityID;

  template <typename T> class ComponentArray : public IComponentArray {
  public:
    void onEntityDestroyed(EntityID id) override {
      throw std::runtime_error("Not implemented");
    }

  public:
    std::vector<T> components;
    std::unordered_map<EntityID, std::array<ComponentTypeID, maxComponents>>
        entityComponentIndexMap;
  };

private:
  EntityManager(const EntityManager &) = delete;
  EntityManager &operator=(const EntityManager &) = delete;

public:
  EntityManager();
  static EntityManager &get();
  ~EntityManager();

  AbstractEntity &createEntity(std::string name = UNNAMED);
  std::vector<Unique<AbstractEntity>> &getEntities();

  AbstractEntity &getEntity(uint32_t id);
  AbstractEntity &getEntity(std::string name);

  uint32_t getEntityID(std::string name);
  uint32_t getEntityID(AbstractEntity &entity);

  std::bitset<maxComponents> getEntityBitset(AbstractEntity &entity);
  void destroyEntity(uint32_t id);
  void destroyEntity(std::string name);
  uint32_t nextID() const;

  template <typename T>
  inline bool hasComponent(const AbstractEntity *entity) const;

  template <typename... TArgs>
  inline bool hasAllComponents(const AbstractEntity *entity) const;

  template <typename T, typename... TArgs>
  inline T &addComponent(AbstractEntity *entity, TArgs &&...mArgs);

  template <typename T> inline T &getComponent(AbstractEntity *entity);

  template <typename... TArgs>
  inline std::vector<AbstractEntity *> &getHasAll();

  template <typename T> inline ComponentArray<T> *getComponentsArray();

  template <typename T> inline void removeComponent(AbstractEntity *entity);

  template <typename T, typename... TArgs>
  inline T &modifyComponent(AbstractEntity *entity, TArgs &&...mArgs);

private:
  std::vector<Unique<AbstractEntity>> entities;

  std::unordered_map<ComponentTypeID, Unique<IComponentArray>> componentArrays;

  std::unordered_map<std::bitset<maxComponents>, std::vector<AbstractEntity *>>
      bitsetEntityMap; // component bitset : entities with those components

  std::unordered_map<EntityID, std::bitset<maxComponents>> entityBitsetMap;

  std::unordered_map<std::string, AbstractEntity *> entityNameMap;
};

template <typename T>
inline bool EntityManager::hasComponent(const AbstractEntity *entity) const {
  return entityBitsetMap.at(entity->getID())[getComponentTypeID<T>()];
}

template <typename T, typename... TArgs>
inline T &EntityManager::addComponent(AbstractEntity *entity,
                                      TArgs &&...mArgs) {
  if (hasComponent<T>(entity)) {
    throw std::runtime_error("Entity already has component");
  }

  auto bitset = entityBitsetMap[entity->getID()];

  // remove from old bitsetEntityMap
  auto it = find(bitsetEntityMap[bitset].begin(), bitsetEntityMap[bitset].end(),
                 entity);

  if (it != bitsetEntityMap[bitset].end()) {
    bitsetEntityMap[bitset].erase(it);
  }

  // add to new bitsetEntityMap
  bitset[getComponentTypeID<T>()] = true;
  bitsetEntityMap[bitset].push_back(entity);
  entityBitsetMap[entity->getID()] = bitset;

  ComponentArray<T> &componentsArr = *getComponentsArray<T>();
  auto &ECM = componentsArr.entityComponentIndexMap;
  if (ECM.find(entity->getID()) == ECM.end()) {
    ECM[entity->getID()].fill(-1);
  }

  componentsArr.components.emplace_back(std::forward<TArgs>(mArgs)...);
  size_t index = componentsArr.components.size() - 1;
  componentsArr
      .entityComponentIndexMap[entity->getID()][getComponentTypeID<T>()] =
      index;

  return componentsArr.components.at(index);
}

template <typename... TArgs>
inline bool
EntityManager::hasAllComponents(const AbstractEntity *entity) const {
  return (hasComponent<TArgs>(entity) && ...);
}

template <typename T>
inline T &EntityManager::getComponent(AbstractEntity *entity) {
  if (!hasComponent<T>(entity)) {
    throw std::runtime_error("Entity does not have component");
  }
  ComponentTypeID CTypeID = getComponentTypeID<T>();

  auto componentsArr = getComponentsArray<T>();
  auto index = componentsArr->entityComponentIndexMap[entity->getID()][CTypeID];
  if (index == -1) {
    throw std::runtime_error("Entity does not have component");
  }
  return componentsArr->components.at(index);
}

template <typename T>
inline void EntityManager::removeComponent(AbstractEntity *entity) {
  if (!hasComponent<T>(entity)) {
    throw std::runtime_error("Entity does not have component");
  }

  auto bitset = entityBitsetMap[entity->getID()];
  auto &es = bitsetEntityMap[bitset];
  for (auto it = es.begin(); it != es.end(); ++it) {
    if ((*it)->getID() == entity->getID()) {
      es.erase(it);
      break;
    }
  }
  bitset[getComponentTypeID<T>()] = false;
  bitsetEntityMap[bitset].push_back(entity);
  entityBitsetMap[entity->getID()] = bitset;

  ComponentArray<T> &componentsArr = *getComponentsArray<T>();
  auto components = componentsArr.components;
  size_t index =
      componentsArr
          .entityComponentIndexMap[entity->getID()][getComponentTypeID<T>()];
  std::swap(components[index], components.back());
  components.pop_back();
  componentsArr
      .entityComponentIndexMap[entity->getID()][getComponentTypeID<T>()] = -1;
}

template <typename T, typename... TArgs>
inline T &EntityManager::modifyComponent(AbstractEntity *entity,
                                         TArgs &&...mArgs) {
  if (!hasComponent<T>(entity)) {
    throw std::runtime_error("Entity does not have component");
  }

  ComponentArray<T> &componentsArr = *getComponentsArray<T>();
  auto &ECM = componentsArr.entityComponentIndexMap;
  auto index = ECM[entity->getID()][getComponentTypeID<T>()];
  if (index == -1) {
    throw std::runtime_error("Entity does not have component");
  }

  componentsArr.components[index] = T(std::forward<TArgs>(mArgs)...);
  return componentsArr.components[index];
}

template <typename T>
inline EntityManager::ComponentArray<T> *EntityManager::getComponentsArray() {
  auto it = componentArrays.find(getComponentTypeID<T>());
  if (it == componentArrays.end()) {
    // create new
    auto componentArray = std::make_unique<ComponentArray<T>>();
    componentArrays[getComponentTypeID<T>()] = std::move(componentArray);
  }

  // Safely cast the IComponentArray to ComponentArray<T>
  ComponentTypeID CTypeID = getComponentTypeID<T>();
  IComponentArray *ica = componentArrays[CTypeID].get();
  auto componentArray = static_cast<ComponentArray<T> *>(ica);
  if (!componentArray) {
    throw std::runtime_error("Invalid component array cast for type T");
  }

  return componentArray;
}

template <typename... TArgs>
inline std::vector<AbstractEntity *> &EntityManager::getHasAll() {
  std::bitset<maxComponents> bitset;
  (bitset.set(getComponentTypeID<TArgs>()), ...);
  return bitsetEntityMap[bitset];
}

#endif // ENTITY_MANAGER_H
