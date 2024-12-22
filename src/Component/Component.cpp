#include "Components/Component.h"

#include "Logger.h"

Component::Component() : entity(nullptr), name("Unnamed") {}
Component::Component(std::string name) : entity(nullptr), name(name) {}

Component::~Component() {
#ifdef _DEBUG
  Log("Component destroyed: " + name);
#endif
  entity = nullptr;
}

std::string Component::getName() const { return name; }

void Component::setEntity(AbstractEntity *_entity) { this->entity = _entity; }
