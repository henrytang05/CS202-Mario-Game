#include "Components/BoundingBox.h"
#include "AbstractEntity.h"
#include "globals.h"
#include "Components/Collision.h"

CollisionComponent::CollisionComponent()
    : Component("CollisionComponent"), entities(nullptr) {}
CollisionComponent::CollisionComponent(Shared<std::vector<Shared<AbstractEntity>>> _entities)
    : Component("CollisionComponent"), entities(_entities) {}

CollisionComponent::~CollisionComponent() {
    entities = nullptr;
}
void CollisionComponent::init() {}
bool isCollision(Rectangle a, Rectangle b) {
    return (a.x <= b.x + b.width &&
        a.x + a.width >= b.x &&
        a.y <= b.y + b.height &&
        a.y + a.height >= b.y);
}
Shared<AbstractEntity> CollisionComponent::standingOn() {
    BoundingBoxComponent &thisBoundingBox = entity->getComponent<BoundingBoxComponent>();
    for(auto &e : *entities) if(*e != *entity) {
        BoundingBoxComponent &otherBoundingBox = e->getComponent<BoundingBoxComponent>();
        if(isCollision(thisBoundingBox.getBotLeft(), otherBoundingBox.getBotRight()) && isCollision(thisBoundingBox.getTopLeft(), otherBoundingBox.getTopRight())) continue;
        if(isCollision(thisBoundingBox.getBotRight(), otherBoundingBox.getBotLeft()) && isCollision(thisBoundingBox.getTopRight(), otherBoundingBox.getTopLeft())) continue;
        if(isCollision(thisBoundingBox.getBotLeft(), otherBoundingBox.getTopLeft())) return e;
        if(isCollision(thisBoundingBox.getBotLeft(), otherBoundingBox.getTopRight())) return e;
        if(isCollision(thisBoundingBox.getBotRight(), otherBoundingBox.getTopLeft())) return e;
        if(isCollision(thisBoundingBox.getBotRight(), otherBoundingBox.getTopRight())) return e;
    }
    return nullptr;
}
Shared<AbstractEntity> CollisionComponent::collisionAbove() {
    BoundingBoxComponent &thisBoundingBox = entity->getComponent<BoundingBoxComponent>();
    for(auto &e : *entities) if(*e != *entity) {
        BoundingBoxComponent &otherBoundingBox = e->getComponent<BoundingBoxComponent>();
        if(isCollision(thisBoundingBox.getBotLeft(), otherBoundingBox.getBotRight()) && isCollision(thisBoundingBox.getTopLeft(), otherBoundingBox.getTopRight())) continue;
        if(isCollision(thisBoundingBox.getBotRight(), otherBoundingBox.getBotLeft()) && isCollision(thisBoundingBox.getTopRight(), otherBoundingBox.getTopLeft())) continue;
        if(isCollision(thisBoundingBox.getTopLeft(), otherBoundingBox.getBotLeft())) return e;
        if(isCollision(thisBoundingBox.getTopLeft(), otherBoundingBox.getBotRight())) return e;
        if(isCollision(thisBoundingBox.getTopRight(), otherBoundingBox.getBotLeft())) return e;
        if(isCollision(thisBoundingBox.getTopRight(), otherBoundingBox.getBotRight())) return e;
    }
    return nullptr;
}
Shared<AbstractEntity> CollisionComponent::collisionSide() {
    BoundingBoxComponent &thisBoundingBox = entity->getComponent<BoundingBoxComponent>();
    for(auto &e : *entities) if(*e != *entity) {
        ASSERT(*e != *entity);
        BoundingBoxComponent &otherBoundingBox = e->getComponent<BoundingBoxComponent>();
        if(isCollision(thisBoundingBox.getBotLeft(), otherBoundingBox.getBotRight()) && isCollision(thisBoundingBox.getTopLeft(), otherBoundingBox.getTopRight())) return e;
        if(isCollision(thisBoundingBox.getBotRight(), otherBoundingBox.getBotLeft()) && isCollision(thisBoundingBox.getTopRight(), otherBoundingBox.getTopLeft())) return e;
    }
    return nullptr;
}
void CollisionComponent::update() {}
void CollisionComponent::setEntities(Shared<std::vector<Shared<AbstractEntity>>> _entities) {
    entities = _entities;
}