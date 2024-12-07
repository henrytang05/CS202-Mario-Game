#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Components/Position.h"
#include "Entity/Entity.h"

class TransformComponent : public Component {
public:
  TransformComponent(Vector2 velocity, float speed);
  void init() override;
  void update() override;
  void setVelocity(Vector2 newVelocity);
  Vector2 getVelocity() const;

private:
  Vector2 velocity;
  float speed;
};

#endif // TRANSFORM_COMPONENT_H
