#include "Components/Rigid.h"
#include "Components/Transform.h"
#include "Entity/Entity.h"

RigidBodyComponent::RigidBodyComponent() : Component("RigidBodyComponent") {}

void RigidBodyComponent::init() {}

void RigidBodyComponent::update() {
  entity->getComponent<TransformComponent>().update();
  entity->getComponent<BoundingBoxComponent>().update();
}
