#ifndef RIGID_BODY_COMPONENT_H
#define RIGID_BODY_COMPONENT_H

#include "Components/BoundingBox.h"
#include "Components/Transform.h"

class RigidBodyComponent : public Component {
public:
  RigidBodyComponent();
  void init() override;
  void update() override;
};

#endif // RIGID_BODY_COMPONENT_H
