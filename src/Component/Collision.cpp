#include "Components/Collision.h"
#include "Components/BoundingBox.h"
#include "EntityManager.h"
#include "globals.h"

CollisionComponent::CollisionComponent() : Component("CollisionComponent") {
  contact.resize(4);
  for (int i = 0; i < 4; i++)
    contact[i].reset();
}
// CollisionComponent::CollisionComponent(
//     Shared<std::vector<Shared<AbstractEntity>>> _entities)
//     : Component("CollisionComponent"){
//   contact.resize(4);
//   for (int i = 0; i < 4; i++)
//     contact[i] = nullptr;
// }

CollisionComponent::~CollisionComponent() {}

Weak<AbstractEntity> CollisionComponent::getBelow() { return contact[2]; }
Weak<AbstractEntity> CollisionComponent::getAbove() { return contact[0]; }
Weak<AbstractEntity> CollisionComponent::getRight() { return contact[3]; }
Weak<AbstractEntity> CollisionComponent::getLeft() { return contact[1]; }

void CollisionComponent::setBelow(Shared<AbstractEntity> other) {
  contact[2] = other;
}
void CollisionComponent::setAbove(Shared<AbstractEntity> other) {
  contact[0] = other;
}
void CollisionComponent::setRight(Shared<AbstractEntity> other) {
  contact[3] = other;
}
void CollisionComponent::setLeft(Shared<AbstractEntity> other) {
  contact[1] = other;
}
