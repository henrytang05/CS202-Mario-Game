#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "Components/Component.h"
#include "raylib.h"

Vector2 operator+(const Vector2 &v1, const Vector2 &v2);

class PositionComponent : public Component {
public:
  PositionComponent();
  PositionComponent(Vector2 pos);
  void setPosition(Vector2 pos);
  Vector2 getPosition();
  float getX();
  float getY();
  void setX(float x);
  void setY(float y);
  void init() override;

private:
  Vector2 position;
};

#endif // POSITION_COMPONENT_H
