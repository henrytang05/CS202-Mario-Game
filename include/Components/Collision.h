#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "Components/Component.h"
#include "raylib.h"

class CollisionComponent : public Component {
public:
    void init() override;
    void update() override;
    void setEntities(Shared<std::vector<Shared<AbstractEntity>>> _entities);
    Shared<AbstractEntity> standingOn();
    Shared<AbstractEntity> collisionAbove();
    Shared<AbstractEntity> collisionSide();
    CollisionComponent();
    ~CollisionComponent();
    CollisionComponent(Shared<std::vector<Shared<AbstractEntity>>> _entities);
private:
    Shared<std::vector<Shared<AbstractEntity>>> entities;
};

#endif // COLLISION_COMPONENT_H
