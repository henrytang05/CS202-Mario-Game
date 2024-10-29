#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#include "ComponentArray.h"
#include "pch.h"

class ComponentManager {
public:
  template <typename T> void RegisterComponent();
  template <typename T> ComponentType GetComponentType();
  template <typename T> void AddComponent(Entity entity, T component);
  template <typename T> void RemoveComponent(Entity entity);
  template <typename T> T &GetComponent(Entity entity);
  inline void EntityDestroyed(Entity entity);

private:
  template <typename T> std::shared_ptr<ComponentArray<T>> GetComponentArray();

private:
  std::unordered_map<const char *, ComponentType> mComponentTypes{};
  std::unordered_map<const char *, Shared<IComponentArray>> mComponentArrays{};
  ComponentType mNextComponentType{};
};

TEMPLATE void ComponentManager::RegisterComponent() {
  const char *typeName = typeid(T).name();

  assert(mComponentTypes.find(typeName) == mComponentTypes.end() &&
         "Registering component type more than once.");

  // Add this component type to the component type map
  mComponentTypes.insert({typeName, mNextComponentType});

  // Create a ComponentArray pointer and add it to the component arrays map
  mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

  // Increment the value so that the next component registered will be
  // different
  ++mNextComponentType;
}

TEMPLATE ComponentType ComponentManager::GetComponentType() {
  const char *typeName = typeid(T).name();

  assert(mComponentTypes.find(typeName) != mComponentTypes.end() &&
         "Component not registered before use.");

  // Return this component's type - used for creating signatures
  return mComponentTypes[typeName];
}

TEMPLATE void ComponentManager::AddComponent(Entity entity, T component) {
  // Add a component to the array for an entity
  GetComponentArray<T>()->InsertData(entity, component);
}
TEMPLATE void ComponentManager::RemoveComponent(Entity entity) {
  // Remove a component from the array for an entity
  GetComponentArray<T>()->RemoveData(entity);
}
TEMPLATE T &ComponentManager::GetComponent(Entity entity) {
  // Get a reference to a component from the array for an entity
  return GetComponentArray<T>()->GetData(entity);
}
void ComponentManager::EntityDestroyed(Entity entity) {
  // Notify each component array that an entity has been destroyed
  // If it has a component for that entity, it will remove it
  for (auto const &pair : mComponentArrays) {
    auto const &component = pair.second;

    component->EntityDestroyed(entity);
  }
}

TEMPLATE std::shared_ptr<ComponentArray<T>>
ComponentManager::GetComponentArray() {
  const char *typeName = typeid(T).name();

  assert(mComponentTypes.find(typeName) != mComponentTypes.end() &&
         "Component not registered before use.");

  return std::static_pointer_cast<ComponentArray<T>>(
      mComponentArrays[typeName]);
}

#endif // COMPONENT_MANAGER_H
