#include "Components/Transform.h"

#include "Components/Position.h"
#include "Entity/Entity.h"
#include "globals.h"
#include "pch.h"

TransformComponent::TransformComponent(Vector2 velocity, float speed)
    : Component("TransformComponent"), velocity(velocity), speed(speed) {}

void TransformComponent::init() {
  if (!entity->hasComponent<PositionComponent>())
    entity->addComponent<PositionComponent>();
}

void TransformComponent::update() {
  PositionComponent &position = entity->getComponent<PositionComponent>();
  position.setPos(position.getPos() + velocity);
}

void TransformComponent::setVelocity(Vector2 newVelocity) {
  velocity = newVelocity;
}

Vector2 TransformComponent::getVelocity() const { return velocity; }
