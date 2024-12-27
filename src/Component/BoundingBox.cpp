#include "Components/BoundingBox.h"
#include "Components/Position.h"
#include "EntityManager.h"
#include "raylib.h"

BoundingBoxComponent::BoundingBoxComponent()
    : Component("BoundingBoxComponent"), Vector2() {}

BoundingBoxComponent::BoundingBoxComponent(Vector2 size)
    : Component("BoundingBoxComponent"), Vector2(size) {}

Vector2 BoundingBoxComponent::getSize() { return {x, y}; }
void BoundingBoxComponent::setSize(Vector2 size) {
  x = size.x;
  y = size.y;
}

void BoundingBoxComponent::to_json(json &j) const { j = *this; }
