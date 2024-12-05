#include "Components/Transform.h"
#include "Components/Position.h"
#include "globals.h"

TransformComponent::TransformComponent() : Component() { init(); }

void TransformComponent::init() {
  // ASSERT(entity->hasComponent<PositionComponent>());

  velocity = {0, 0};
  speed = 0;
}

void TransformComponent::update() {
  PositionComponent &position = entity->getComponent<PositionComponent>();
  position.setPos(position.getPos() + velocity);
}
