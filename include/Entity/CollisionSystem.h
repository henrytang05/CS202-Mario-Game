#pragma once

#include "AbstractEntity.h"

class CollisionSystem {
public:
  CollisionSystem(std::vector<Shared<AbstractEntity>> &_entities);
  bool isCollision(Rectangle a, Rectangle b);
  Shared<AbstractEntity> standingOn();
  Shared<AbstractEntity> collisionAbove();
  Shared<AbstractEntity> collisionSide();

private:
  std::vector<Shared<AbstractEntity>> &entities;
};
