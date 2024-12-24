#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "Component.h"
#include "EntityManager.h"
#include "Interface.h"
#include "raylib.h"

class CollisionComponent : public Component {
public:
  Weak<AbstractEntity> getBelow();
  Weak<AbstractEntity> getAbove();
  Weak<AbstractEntity> getRight();
  Weak<AbstractEntity> getLeft();
  void setBelow(Shared<AbstractEntity> other);
  void setAbove(Shared<AbstractEntity> other);
  void setRight(Shared<AbstractEntity> other);
  void setLeft(Shared<AbstractEntity> other);
  void reset();

  CollisionComponent();
  ~CollisionComponent();

public:
  std::vector<Weak<AbstractEntity>> contact;
};

#endif // COLLISION_COMPONENT_H
