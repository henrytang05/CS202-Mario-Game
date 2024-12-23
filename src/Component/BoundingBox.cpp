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
Vector2 BoundingBoxComponent::getSize() { return this->size;}
void BoundingBoxComponent::setSize(Vector2 size) { this->size = size; }
void BoundingBoxComponent::update(float deltaTime) {}
