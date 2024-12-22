#ifndef COMPONENT_H
#define COMPONENT_H
#include "AbstractEntity.h"
#include "EntityManager.h"

class Component {
public:
  Component();
  Component(std::string name);
  virtual ~Component();

  void setEntity(AbstractEntity *e);
  std::string getName() const;

protected:
  AbstractEntity *entity;
  const std::string name;
  EntityManager &EM = EntityManager::get();
};

#endif // COMPONENT_H
