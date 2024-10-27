#ifndef ENTITY_H
#define ENTITY_H
#include "../Component/Component.h"

class Entity {
public:
  Entity();
  ~Entity();

private:
  Component *components;
};

#endif // ENTITY_H
