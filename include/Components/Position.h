#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "Components/Component.h"
#include "raylib.h"

Vector2 operator+(const Vector2 &v1, const Vector2 &v2);
Vector2 operator-(const Vector2 &v);

class PositionComponent : public Component, public Vector2 {
public:
  PositionComponent();
  PositionComponent(Vector2 pos);
  PositionComponent(float x, float y);
  ~PositionComponent();

  void setPosition(Vector2 pos);
  Vector2 getPosition();
};

class TransformComponent : public Component, public Vector2 {
public:
  TransformComponent(Vector2 pos);
  TransformComponent(float x, float y);
  TransformComponent();
  ~TransformComponent();

  void setVelocity(Vector2 pos);
  Vector2 getVelocity();
};

#endif // POSITION_COMPONENT_H
