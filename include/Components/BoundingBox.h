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
  void update(float deltaTime) override;
  Vector2 getSize();
  Rectangle getTopLeft();
  Rectangle getTopRight();
  Rectangle getBotLeft();
  Rectangle getBotRight();

private:
  PositionComponent *position;
  Vector2 size;
};
#endif // BOUNDINGBOX_H
