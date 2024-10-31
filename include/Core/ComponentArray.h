#ifndef COMPONENT_ARRAY_H
#define COMPONENT_ARRAY_H

#include "pch.h"

#include "EntityComponent.h"
class IComponentArray {
public:
  virtual ~IComponentArray() = default;
  virtual void EntityDestroyed(Entity entity) = 0;
};
TEMPLATE
class ComponentArray : public IComponentArray {
public:
  void InsertData(Entity entity, const T &component);
  void EntityDestroyed(Entity entity) override;
  T &GetData(Entity entity);
  ~ComponentArray() {}

private:
  void RemoveData(Entity entity);
  std::array<T, MAX_ENTITIES> mComponentArray;

  std::unordered_map<Entity, size_t> mEntityToIndexMap;
  std::unordered_map<size_t, Entity> mIndexToEntityMap;

  size_t mSize;
};

TEMPLATE
void ComponentArray<T>::InsertData(Entity entity, const T &component) {

  assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() &&
         "Component added to same entity more than once.");

  size_t newIndex = mSize;

  mEntityToIndexMap[entity] = newIndex;
  mIndexToEntityMap[newIndex] = entity;
  mComponentArray[newIndex] = component;
  ++mSize;
}

TEMPLATE
void ComponentArray<T>::RemoveData(Entity entity) {
  assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() &&
         "Removing non-existent component.");

  // Copy element at end into deleted element's place to maintain density
  size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
  size_t indexOfLastElement = mSize - 1;
  mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

  // Update map to point to moved spot
  Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
  mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
  mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

  mEntityToIndexMap.erase(entity);
  mIndexToEntityMap.erase(indexOfLastElement);

  --mSize;
}

TEMPLATE
T &ComponentArray<T>::GetData(Entity entity) {
  assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() &&
         "Retrieving non-existent component.");

  return mComponentArray[mEntityToIndexMap[entity]];
}

TEMPLATE
void ComponentArray<T>::EntityDestroyed(Entity entity) {
  if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()) {
    RemoveData(entity);
  }
}

#endif
