#ifndef COMPONENT_H
#define COMPONENT_H
#include "EntityManager.h"

class Component {
public:
  Component();
  Component(std::string name);
  virtual ~Component();

  void setEntity(AbstractEntity *e);
  std::string getName() const;

private:
  EntityManager &manager = EntityManager::get();
  const std::string name;
};

#endif // COMPONENT_H
