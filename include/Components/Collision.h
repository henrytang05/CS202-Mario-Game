#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "Components/Component.h"
#include "raylib.h"

class CollisionComponent : public Component {
public:
    void init() override;
    void update(float deltaTime) override;
    void setEntities(Shared<std::vector<Shared<AbstractEntity>>> _entities);
    bool DynamicRectVsRect(const float deltaTime, const Rectangle &r_static, Vector2& contact_point, Vector2& contact_normal, float& contact_time);
    bool ResolveDynamicRectVsRect(const float deltaTime, Shared<AbstractEntity> r_static);
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
    CollisionComponent(Shared<std::vector<Shared<AbstractEntity>>> _entities);
private:
    std::vector<Shared<AbstractEntity>> contact;
    Shared<std::vector<Shared<AbstractEntity>>> entities;
};

#endif // COLLISION_COMPONENT_H
