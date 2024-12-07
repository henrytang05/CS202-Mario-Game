#ifndef ENTITY_H
#define ENTITY_H

#include "Components/Component.h"
#include "Interface.h"
#include "Logger.h"
#include "globals.h"

class Component;

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

  template <typename T> bool hasComponent() const;

  template <typename T, typename... TArgs> T &addComponent(TArgs &&...mArgs);

  template <typename T> T &getComponent() const;

public:
  bool active;
  std::string name;
  std::vector<Unique<Component>> components;
  ComponentArray componentArray;
  ComponentBitSet componentBitset;
};

#include "Entity/Entity_impl.hpp"

#endif // ENTITY_H
