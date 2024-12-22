#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "Components/Component.h"
#include "raylib.h"

class CollisionComponent : public Component {
public:
    void init() override;
    void update(float deltaTime) override;
    void setEntities(std::vector<Shared<AbstractEntity>> *entities);
    bool DynamicRectVsRect(const float deltaTime, const Rectangle &r_static, Vector2& contact_point, Vector2& contact_normal, float& contact_time);
    bool ResolveDynamicRectVsRect(const float deltaTime, Weak<AbstractEntity> r_static);
    Weak<AbstractEntity> getBelow();
    Weak<AbstractEntity> getAbove();
    Weak<AbstractEntity> getRight();
    Weak<AbstractEntity> getLeft();
    void setBelow(Weak<AbstractEntity> other);
    void setAbove(Weak<AbstractEntity> other);
    void setRight(Weak<AbstractEntity> other);
    void setLeft(Weak<AbstractEntity> other);
    void reset();
    CollisionComponent();
    ~CollisionComponent();
    CollisionComponent(std::vector<Shared<AbstractEntity>> *entities);
private:
    std::vector<Weak<AbstractEntity>> contact;
    std::vector<Shared<AbstractEntity>> *entities;
};

#endif // COLLISION_COMPONENT_H
