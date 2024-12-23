#include "Components/BoundingBox.h"
#include "Components/Position.h"
#include "EntityManager.h"
#include "raylib.h"

BoundingBoxComponent::BoundingBoxComponent()
    : Component("BoundingBoxComponent"), Vector2(), position(nullptr) {}

BoundingBoxComponent::BoundingBoxComponent(Vector2 size)
    : Component("BoundingBoxComponent"), Vector2(size), position(nullptr) {}

Vector2 BoundingBoxComponent::getSize() { return {x, y}; }
void BoundingBoxComponent::setSize(Vector2 size) {
  x = size.x;
  y = size.y;
}
Rectangle BoundingBoxComponent::getTopLeft() {
  Rectangle result;
  result.x = position->x;
  result.y = position->y;
  result.width = x / 2.0f;
  result.height = y / 2.0f;
  return result;
}
Rectangle BoundingBoxComponent::getTopRight() {
  Rectangle result;
  result.x = position->x + getTopLeft().width;
  result.y = position->y;
  result.width = x - getTopLeft().width;
  result.height = y / 2.0f;
  return result;
}
Rectangle BoundingBoxComponent::getBotLeft() {
  Rectangle result;
  result.x = position->x;
  result.y = position->y + getTopLeft().height;
  result.width = x / 2.0f;
  result.height = y - getTopLeft().height;
  return result;
}
Rectangle BoundingBoxComponent::getBotRight() {
  Rectangle result;
  result.x = position->x + getTopLeft().width;
  result.y = position->y + getTopLeft().height;
  result.width = x - getTopLeft().width;
  result.height = y - getTopLeft().height;
  return result;
}
