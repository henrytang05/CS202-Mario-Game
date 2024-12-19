#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include "Components/Component.h"
#include "Interface.h"
#include "Logger.h"
#include <cstdint>

class AbstractEntity : public IUpdatable, public IDrawable {
public:
  AbstractEntity() : active(true), name("Unnamed") { id = nextID(); }
  AbstractEntity(std::string name) : active(true), name(name) { id = nextID(); }
  virtual ~AbstractEntity() {
#ifdef _DEBUG
    Log(name + " created: " + std::to_string(id));
#endif
  }
  template <typename T> inline bool hasComponent() const;
  template <typename... TArgs> inline bool hasAllComponents() const;
  template <typename T, typename... TArgs>
  inline T &addComponent(TArgs &&...mArgs);
  template <typename T> inline T &getComponent() const;

  uint32_t getId() const { return id; }
  bool operator==(const AbstractEntity &other) const { return id == other.id; }
  bool operator!=(const AbstractEntity &other) const { return id != other.id; }

  bool isActive() const { return active; }
  void destroy() { active = false; }

private:
  uint32_t nextID() const {
    static uint32_t nextID = 0;
    return nextID++;
  }

public:
  bool active;
  std::string name;
  std::vector<Unique<Component>> components;

private:
  uint32_t id;
  ComponentArray componentArray;
  ComponentBitSet componentBitset;
};

template <typename T> inline bool AbstractEntity::hasComponent() const {
  ComponentTypeID typeID = getComponentTypeID<T>();

  if (typeID >= maxComponents) {
    Log("Exceeded maximum number of components", LogLevel::ERROR, "log.txt");
    return false;
  }
  return this->componentBitset.test(typeID);
}

template <typename... TArgs>
inline bool AbstractEntity::hasAllComponents() const {
  return (hasComponent<TArgs>() && ...);
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
  Log("Component added: " + c->name);
#endif
  return *c;
}

template <typename T> inline T &AbstractEntity::getComponent() const {
  auto ptr(componentArray[getComponentTypeID<T>()]);
  return *static_cast<T *>(ptr);
}

#endif // ABSTRACTENTITY_H
