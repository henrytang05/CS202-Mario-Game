#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Components/Component.h"
#include "Components/Position.h"
class BoundingBoxComponent : public Component {
public:
  BoundingBoxComponent();

  void init() override;
  void setSize(Vector2 size);
  void update() override;
  Vector2 getPos();
  float getX() const;
  float getY() const;
  void setX(float x);
  void setY(float y);

  bool isOnTheGround() { return position->getY() + size.y >= ground; }

private:
  Shared<PositionComponent> position;
  Vector2 size;
};
#endif // BOUNDINGBOX_H
