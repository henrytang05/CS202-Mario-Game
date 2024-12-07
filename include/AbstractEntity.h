#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include "Components/Component.h"
#include "Logger.h"

class AbstractEntity {
public:
  AbstractEntity() = default;
  virtual ~AbstractEntity() = default;
  template <typename T> bool hasComponent() const;
  template <typename T, typename... TArgs> T &addComponent(TArgs &&...mArgs);
  template <typename T> T &getComponent() const;

  bool isActive() const { return active; }
  void destroy() { active = false; }

public:
  bool active = true;
  std::vector<Unique<Component>> components;
  ComponentArray componentArray;
  ComponentBitSet componentBitset;
};

template <typename T> inline bool AbstractEntity::hasComponent() const {
  ComponentTypeID typeID = getComponentTypeID<T>();

  if (typeID >= maxComponents) {
    Log("log.txt", LogLevel::CRITICAL, "Exceeded maximum number of components");
    return false;
  }
  return this->componentBitset.test(typeID);
}

template <typename T, typename... TArgs>
inline T &AbstractEntity::addComponent(TArgs &&...mArgs) {
  ComponentTypeID typeID = getComponentTypeID<T>();
  if (typeID >= maxComponents) {
    throw std::runtime_error("Exceeded maximum number of components");
  }
  T *c(new T(std::forward<TArgs>(mArgs)...));
  c->setEntity(this);

  // Unique<Component> uPtr{c};
  // components.emplace_back(std::move(uPtr));
  components.push_back(Unique<Component>(c));

  componentArray[getComponentTypeID<T>()] = c;
  componentBitset[getComponentTypeID<T>()] = true;
  c->init();

#ifdef _DEBUG
  Log("log.txt", LogLevel::INFO, c->name + " created");
#endif
  return *c;
}

template <typename T> inline T &AbstractEntity::getComponent() const {
  auto ptr(componentArray[getComponentTypeID<T>()]);
  return *static_cast<T *>(ptr);
}
#endif // ABSTRACTENTITY_H
