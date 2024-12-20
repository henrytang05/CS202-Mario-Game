#ifndef SYSTEM_H
#define SYSTEM_H

#include "AbstractEntity.h"
class System {

public:
  virtual ~System() = default;
  virtual void update(Shared<AbstractEntity> entity, float dt) = 0;
};

class TransformSystem : public System {
public:
  void update(Shared<AbstractEntity> entity, float dt) override;
};

class AnimationSystem : public System {
  void update(Shared<AbstractEntity> entity, float dt) override;
};

#endif // SYSTEM_H
