#include "Components/Position.h"

#include "globals.h"

PositionComponent::PositionComponent()
    : Component("PositionComponent"), position({0, 0}) {}

PositionComponent::PositionComponent(Vector2 pos)
    : Component("PositionComponent") {
  position = pos;
}

void PositionComponent::init() {}

void PositionComponent::setPosition(Vector2 pos) { position = pos; }
Vector2 PositionComponent::getPosition() const { return position; }
float PositionComponent::getX() const { return position.x; }
float PositionComponent::getY() const { return position.y; }

void PositionComponent::setX(float x) { position.x = x; }
void PositionComponent::setY(float y) { position.y = y; }

Vector2 operator+(const Vector2 &v1, const Vector2 &v2) {
  return {v1.x + v2.x, v1.y + v2.y};
}
