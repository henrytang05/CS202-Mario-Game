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
Vector2 BoundingBoxComponent::getSize() { return this->size;}
void BoundingBoxComponent::setSize(Vector2 size) { this->size = size; }
Rectangle BoundingBoxComponent::getTopLeft() {
  Rectangle result;
  result.x = position->getX();
  result.y = position->getY();
  result.width = size.x / 2.0f;
  result.height = size.y / 2.0f;
  return result;
}
Rectangle BoundingBoxComponent::getTopRight() {
  Rectangle result;
  result.x = position->getX() + getTopLeft().width;
  result.y = position->getY();
  result.width = size.x - getTopLeft().width;
  result.height = size.y / 2.0f;
  return result;
}
Rectangle BoundingBoxComponent::getBotLeft() {
  Rectangle result;
  result.x = position->getX();
  result.y = position->getY() + getTopLeft().height;
  result.width = size.x / 2.0f;
  result.height = size.y - getTopLeft().height;
  return result;
}
Rectangle BoundingBoxComponent::getBotRight() {
  Rectangle result;
  result.x = position->getX() + getTopLeft().width;
  result.y = position->getY() + getTopLeft().height;
  result.width = size.x - getTopLeft().width;
  result.height = size.y - getTopLeft().height;
  return result;
}
void BoundingBoxComponent::update(float deltaTime) {}