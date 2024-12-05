#include "Components/Rigid.h"

#include "Components/Transform.h"

RigidBodyComponent::RigidBodyComponent() : Component() { init(); }

void RigidBodyComponent::init() {}

void RigidBodyComponent::update() {
    entity->getComponent<TransformComponent>().update();
    entity->getComponent<BoundingBoxComponent>().update();
}
