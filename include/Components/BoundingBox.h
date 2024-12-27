#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Components/Position.h"
#include "globals.h"

class BoundingBoxComponent : public Component, public Vector2 {

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(BoundingBoxComponent, x, y)
public:
  BoundingBoxComponent();
  BoundingBoxComponent(Vector2 _size);

  void setSize(Vector2 size);
  Vector2 getSize();

  void to_json(json &j) const override;
};
#endif // BOUNDINGBOX_H
