#include "Components/Rigid.h"

#include "Components/Transform.h"

RigidBodyComponent::RigidBodyComponent(Entity *e) : Component(e) {
  init();

#ifdef _DEBUG
  Log("log.txt", LogLevel::INFO, name + " created");
#endif
}

void RigidBodyComponent::init() { name = "RigidBodyComponent"; }

void RigidBodyComponent::update() {
  entity->getComponent<TransformComponent>().update();
  entity->getComponent<BoundingBoxComponent>().update();
}
