#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "Entity/Entity.h"
#include "raylib.h"

Vector2 operator+(const Vector2 &v1, const Vector2 &v2);

class PositionComponent : public Component {
public:
  PositionComponent();
  void setPos(Vector2 pos);
  Vector2 getPos() const;
  float getX() const;
  float getY() const;
  void setX(float x);
  void setY(float y);

private:
  Vector2 position;
};

#endif // POSITION_COMPONENT_H
