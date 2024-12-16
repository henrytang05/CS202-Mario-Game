#include "Components/Transform.h"

#include "AbstractEntity.h"
#include "Components/Position.h"
#include "Components/Collision.h"
#include "Components/BoundingBox.h"
#include "globals.h"

TransformComponent::TransformComponent(Vector2 velocity)
    : Component("TransformComponent"), velocity(velocity) {}

void TransformComponent::init() {
  if (!entity->hasComponent<PositionComponent>())
    entity->addComponent<PositionComponent>();
}

void TransformComponent::update() {
  PositionComponent &position = entity->getComponent<PositionComponent>();
  position.setPosition(position.getPosition() + velocity);
  if(entity->hasComponent<CollisionComponent>()) {
    Shared<AbstractEntity> e = entity->getComponent<CollisionComponent>().collisionSide();
    if(e != nullptr) {
      if(e->getComponent<PositionComponent>().getX() <= position.getX()) {
        position.setPosition((Vector2){e->getComponent<PositionComponent>().getX() + e->getComponent<BoundingBoxComponent>().getSize().x + 1, 
                                       position.getY()});
      }
      else {
        position.setPosition((Vector2){e->getComponent<PositionComponent>().getX() - entity->getComponent<BoundingBoxComponent>().getSize().x - 1, 
                                       position.getY()});
      }
    }
  }
}

void TransformComponent::setVelocity(Vector2 newVelocity) {
  velocity = newVelocity;
}

Vector2 TransformComponent::getVelocity() const { return velocity; }
