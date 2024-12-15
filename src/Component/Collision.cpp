#include "Components/Collision.h"
#include "Components/BoundingBox.h"
#include "AbstractEntity.h"
#include "globals.h"

CollisionComponent::CollisionComponent()
    : Component("CollisionComponent"), entities(nullptr) {}
CollisionComponent::CollisionComponent(std::vector<Shared<AbstractEntity>> *_entities)
    : Component("CollisionComponent"), entities(_entities) {}
void CollisionComponent::init() {}
bool isCollision(Rectangle a, Rectangle b) {
    
}
void CollisionComponent::update() {
    for(auto &e : *entities) if(e != entity) {
        
    }
}
void CollisionComponent::setEntities(std::vector<Shared<AbstractEntity>> *_entities) {
    entities = _entities;
}