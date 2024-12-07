#ifndef ENTITY_H
#define ENTITY_H

#include "AbstractEntity.h"

class Component;

class Entity : public AbstractEntity {

public:
  Entity();
  Entity(std::string name);
  virtual ~Entity();

public:
  std::string name;
};

#endif // ENTITY_H
