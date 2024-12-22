#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "AbstractEntity.h"
#include "Components/Component.h"
#include "Interface.h"
#include "raylib.h"

class CollisionComponent : public Component, public IUpdatable {
public:
  Shared<AbstractEntity> getBelow();
  Shared<AbstractEntity> getAbove();
  Shared<AbstractEntity> getRight();
  Shared<AbstractEntity> getLeft();
  void setBelow(Shared<AbstractEntity> other);
  void setAbove(Shared<AbstractEntity> other);
  void setRight(Shared<AbstractEntity> other);
  void setLeft(Shared<AbstractEntity> other);
  void reset();

  CollisionComponent();
  ~CollisionComponent();

public:
  std::vector<AbstractEntity *> contact;
};

#endif // COLLISION_COMPONENT_H
