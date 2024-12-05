#ifndef CAMERA_H
#define CAMERA_H

#include "Entity/Entity.h"

class CameraComponent : public Component, public Camera2D {
public:
  CameraComponent(Entity *e);
  void init() override;
  void update() override;
  void setTarget(Vector2 target);
};

#endif // CAMERA_H
