#ifndef CAMERA_H
#define CAMERA_H

#include "AbstractEntity.h"
class CameraComponent : public Component, public Camera2D {
public:
  CameraComponent();
  void init() override;
  void update() override;
  void setTarget(Vector2 target);
  void setTarget(AbstractEntity &target);
};

#endif // CAMERA_H
