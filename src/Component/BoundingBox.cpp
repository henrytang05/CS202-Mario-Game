#include "Components/BoundingBox.h"
#include "AbstractEntity.h"
#include "Components/Position.h"
#include "globals.h"
#include "raylib.h"

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
  return position->getY() + size.y >= ground;
}

void BoundingBoxComponent::setSize(Vector2 size) { this->size = size; }

Vector2 BoundingBoxComponent::getPos() { return position->getPosition(); }
void BoundingBoxComponent::setPos(Vector2 pos) { position->setPosition(pos); }

float BoundingBoxComponent::getX() const { return position->getX(); }
float BoundingBoxComponent::getY() const { return position->getY(); }
void BoundingBoxComponent::setX(float x) { position->setX(x); }
void BoundingBoxComponent::setY(float y) { position->setY(y); }

void BoundingBoxComponent::update() {
  if (position->getX() <= 0)
    position->setX(0.0f);
  if (position->getX() + size.x >= screenWidth)
    position->setX(screenWidth - size.x);
}

Rectangle BoundingBoxComponent::getBox() const {
  return (Rectangle){position->getX(), position->getY(), size.x, size.y};
}

bool BoundingBoxComponent::checkCollision(
    const BoundingBoxComponent &other) const {

  Rectangle box = this->getBox();
  Rectangle otherBox = other.getBox();

  return (box.x <= otherBox.x + otherBox.width &&
          box.x + box.width >= otherBox.x &&
          box.y <= otherBox.y + otherBox.height &&
          box.y + box.height >= otherBox.y);
}
