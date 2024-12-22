#ifndef SYSTEM_H
#define SYSTEM_H

#include "EntityManager.h"
class System {

public:
  virtual ~System() = default;
  virtual void update(EntityManager &EM, float dt) = 0;
};

class TransformSystem : public System {
public:
  void update(EntityManager &EM, float dt) override;
};

class AnimationSystem : public System {
  void update(EntityManager &EM, float dt) override;
};

#endif // SYSTEM_H
