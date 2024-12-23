#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Components/Position.h"
#include "globals.h"

class BoundingBoxComponent : public Component, public Vector2 {
public:
  BoundingBoxComponent();
  BoundingBoxComponent(Vector2 _size);

  void setSize(Vector2 size);
  Vector2 getSize();

private:
  PositionComponent *position;
};
#endif // BOUNDINGBOX_H
