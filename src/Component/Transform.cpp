#include "Components/Transform.h"

#include "AbstractEntity.h"
#include "Components/BoundingBox.h"
#include "Components/Collision.h"
#include "Components/Position.h"
#include "Components/Tags.h"
#include "globals.h"

TransformComponent::TransformComponent(Vector2 velocity)
    : Component("TransformComponent"), velocity(velocity) {}

void TransformComponent::init() {
  if (!entity->hasComponent<PositionComponent>())
    entity->addComponent<PositionComponent>();
}

void TransformComponent::update(float deltaTime) {}
void TransformComponent::setVelocity(Vector2 newVelocity) {
  velocity = newVelocity;
}

Vector2 TransformComponent::getVelocity() const { return velocity; }

Vector2 TransformComponent::operator-() const {
  return Vector2{-velocity.x, -velocity.y};
}
