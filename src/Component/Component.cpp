#include "Components/Component.h"

#include "Logger.h"

Component::Component(std::string name, AbstractEntity *e, EntityManager *em)
    : entity(e), EM(em), name(std::move(name)) {}

Component::~Component() {
#ifdef _DEBUG
  Log("Component destroyed: " + name);
#endif
  entity = nullptr;
}

std::string Component::getName() const { return name; }

void Component::setEntity(AbstractEntity *_entity) { this->entity = _entity; }

void Component::setEntityManager(EntityManager *em) { EM = em; }
