#include "Components/Position.h"

PositionComponent::PositionComponent(Vector2 pos)
    : Component("PositionComponent"), Vector2({pos.x, pos.y}) {}
PositionComponent::PositionComponent(float x, float y)
    : Component("PositionComponent"), Vector2({x, y}) {}
PositionComponent::PositionComponent()
    : Component("PositionComponent"), Vector2({0, 0}) {}
PositionComponent::~PositionComponent() = default;

void PositionComponent::setPosition(Vector2 pos) {
  x = pos.x;
  y = pos.y;
}

Vector2 PositionComponent::getPosition() { return {x, y}; }

void PositionComponent::accept(Exporter &exporter) { exporter.visit(*this); }

Vector2 operator+(const Vector2 &v1, const Vector2 &v2) {
  return {v1.x + v2.x, v1.y + v2.y};
}

TransformComponent::TransformComponent(Vector2 pos)
    : Component("TransformComponent"), Vector2({pos.x, pos.y}) {}
TransformComponent::TransformComponent(float x, float y)
    : Component("TransformComponent"), Vector2({x, y}) {}
TransformComponent::TransformComponent()
    : Component("TransformComponent"), Vector2({0, 0}) {}
TransformComponent::~TransformComponent() = default;

void TransformComponent::setVelocity(Vector2 pos) {
  x = pos.x;
  y = pos.y;
}

Vector2 TransformComponent::getVelocity() { return {x, y}; }

Vector2 operator-(const Vector2 &v) { return {-v.x, -v.y}; }
