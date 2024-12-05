#ifndef CAMERA_H
#define CAMERA_H

#include "Entity/Entity.h"

class CameraComponent : public Component, public Camera2D {
public:
  CameraComponent();
  void init();
  void update() override;
  void setTarget(Vector2 target);
};

#endif // CAMERA_H
