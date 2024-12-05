#ifndef RIGID_BODY_COMPONENT_H
#define RIGID_BODY_COMPONENT_H

#include "Components/BoundingBox.h"
#include "Components/Transform.h"

class RigidBodyComponent : public Component {
public:
  RigidBodyComponent();
  void init();
  void update() override;
};

#endif // RIGID_BODY_COMPONENT_H
