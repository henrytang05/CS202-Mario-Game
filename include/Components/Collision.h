#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "Components/Component.h"
#include "raylib.h"

class CollisionComponent : public Component {
public:
    void init() override;
    void update() override;
    void setEntities(std::vector<Shared<AbstractEntity>> *_entities);
    CollisionComponent();
    CollisionComponent(std::vector<Shared<AbstractEntity>> *_entities);
private:
    std::vector<Shared<AbstractEntity>> *entities;
};

#endif // COLLISION_COMPONENT_H
