#include "Components/BoundingBox.h"
#include "Components/Position.h"
#include "Entity/Entity.h"
#include "globals.h"

BoundingBoxComponent::BoundingBoxComponent()
    : Component("BoundingBoxComponent"), position(nullptr), size({0, 0}) {}

BoundingBoxComponent::BoundingBoxComponent(Vector2 size)
    : Component("BoundingBoxComponent"), position(nullptr), size(size) {}

void BoundingBoxComponent::init() {
  if (!entity->hasComponent<PositionComponent>())
    entity->addComponent<PositionComponent>();

  position = &entity->getComponent<PositionComponent>();
}
bool BoundingBoxComponent::isOnTheGround() {
  return position->getY() + size.y + 0.51 >= ground;
}

void BoundingBoxComponent::setSize(Vector2 size) { this->size = size; }

Vector2 BoundingBoxComponent::getPos() { return position->getPos(); }
void BoundingBoxComponent::setPos(Vector2 pos) { position->setPos(pos); }

float BoundingBoxComponent::getX() const { return position->getX(); }
float BoundingBoxComponent::getY() const { return position->getY(); }
void BoundingBoxComponent::setX(float x) { position->setX(x); }
void BoundingBoxComponent::setY(float y) { position->setY(y); }

void BoundingBoxComponent::update() {
  if (position->getX() <= 0)
    position->setX(0.0f);
  if (position->getX() + size.x >= screenWidth)
    position->setX(screenWidth - size.x);
  if (position->getY() + size.y >= ground)
    position->setY(ground - size.y);
}
