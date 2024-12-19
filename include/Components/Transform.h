#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Components/Position.h"

class TransformComponent : public Component {
public:
  TransformComponent(Vector2 velocity);
  void init() override;
  void update(float deltaTime) override;
  void setVelocity(Vector2 newVelocity);
  Vector2 getVelocity() const;
  Vector2 operator-() const;

private:
  Vector2 velocity;
};

#endif // TRANSFORM_COMPONENT_H
