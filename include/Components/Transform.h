#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Components/Position.h"
#include "Entity/Entity.h"

class TransformComponent : public Component {
public:
  TransformComponent();
  void init();
  void update() override;

private:
  Vector2 velocity;
  float speed;
};

#endif // TRANSFORM_COMPONENT_H
