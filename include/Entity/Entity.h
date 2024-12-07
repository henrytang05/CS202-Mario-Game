#ifndef ENTITY_H
#define ENTITY_H

#include "AbstractEntity.h"
#include "Interface.h"

class Component;

class Entity : public AbstractEntity, public IUpdatable {

public:
  Entity();
  Entity(std::string name);
  virtual ~Entity();
  void update() override;

public:
  std::string name;
};

#endif // ENTITY_H
