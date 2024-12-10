#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Components/Component.h"
#include "Components/Position.h"
#include "globals.h"

class BoundingBoxComponent : public Component {
public:
  BoundingBoxComponent();
  BoundingBoxComponent(Vector2 _size);

  void init() override;
  void setSize(Vector2 size);
  void update() override;
  Vector2 getPos();
  void setPos(Vector2 pos);
  float getX() const;
  float getY() const;
  void setX(float x);
  void setY(float y);

  bool checkCollision(const BoundingBoxComponent &other) const;
  bool isOnTheGround();

  Rectangle getBox() const;

private:
  PositionComponent *position;
  Vector2 size;
};
#endif // BOUNDINGBOX_H
