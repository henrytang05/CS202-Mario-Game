#ifndef ENTITY_H
#define ENTITY_H

#include "Interface.h"
#include "Logger.h"
#include "globals.h"

class Entity;
class Component;

using ComponentTypeID = std::size_t;

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component *, maxComponents>;

inline ComponentTypeID getComponentTypeID() {
  static ComponentTypeID lastID = 0;
  return lastID++;
}

template <typename T> inline ComponentTypeID getComponentTypeID() noexcept {
  static ComponentTypeID typeID = getComponentTypeID();
  return typeID;
}

class Component {
public:
  Component() : entity(nullptr) {}
  virtual ~Component() = default;
  virtual void init() {}
  virtual void update() {};
  virtual void draw() {};
  void setEntity(Shared<Entity> e) { entity = e; }
  void setEntity(Entity *e) { entity = Shared<Entity>(e); }

protected:
  Shared<Entity> entity;
};

class Entity : public IUpdatable {
public:
  Entity();
  Entity(std::string name);
  virtual ~Entity();
  void init();

  void update();
  void draw();
  bool isActive() const;
  void destroy();

  void setVelocity(Vector2 newVelocity);

  template <typename T> bool hasComponent() const {
    ComponentTypeID typeID = getComponentTypeID<T>();

    if (typeID >= maxComponents) {
      Log("log.txt", LogLevel::CRITICAL,
          "Exceeded maximum number of components");
      return false;
    }
    return componentBitset.test(typeID);
  }

  template <typename T, typename... TArgs> T &addComponent(TArgs &&...mArgs) {
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
    return *c;
  }

  template <typename T> T &getComponent() const {
    auto ptr(componentArray[getComponentTypeID<T>()]);
    return *static_cast<T *>(ptr);
  }

public:
  bool active;
  std::string name;
  std::vector<Unique<Component>> components;
  ComponentArray componentArray;
  ComponentBitSet componentBitset;
};

#endif // ENTITY_H
