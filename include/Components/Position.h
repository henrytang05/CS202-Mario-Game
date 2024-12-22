#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "Components/Component.h"
#include "raylib.h"

Vector2 operator+(const Vector2 &v1, const Vector2 &v2);

class PositionComponent : public Component, public Vector2 {
public:
  PositionComponent(Vector2 pos)
      : Component("PositionComponent"), Vector2(pos) {}
  PositionComponent(float x, float y)
      : Component("PositionComponent"), Vector2(x, y) {}
  PositionComponent() : Component("PositionComponent"), Vector2({0, 0}) {}
  ~PositionComponent() = default;

  void setPosition(Vector2 pos) {
    x = pos.x;
    y = pos.y;
  }
  Vector2 getPosition() { return {x, y}; }
};

class TransformComponent : public Component, public Vector2 {
public:
  TransformComponent(Vector2 pos)
      : Component("TransformComponent"), Vector2(pos) {}
  TransformComponent(float x, float y)
      : Component("TransformComponent"), Vector2(x, y) {}
  TransformComponent() : Component("TransformComponent"), Vector2({0, 0}) {}
  ~TransformComponent() = default;

  void setVelocity(Vector2 pos) {
    x = pos.x;
    y = pos.y;
  }
  Vector2 getVelocity() { return {x, y}; }
};

class BoundingBoxComponent : public Component, public Vector2 {
public:
  BoundingBoxComponent(Vector2 size)
      : Component("BoundingBoxComponent"), Vector2(size) {}
  BoundingBoxComponent(float x, float y)
      : Component("BoundingBoxComponent"), Vector2(x, y) {}
  BoundingBoxComponent() : Component("BoundingBoxComponent"), Vector2({0, 0}) {}
  ~BoundingBoxComponent() = default;

  void setSize(Vector2 size);
  Vector2 getSize();
};

#endif // POSITION_COMPONENT_H
