#include "Components/BoundingBox.h"
#include "AbstractEntity.h"
#include "Components/Position.h"
#include "globals.h"
#include "raylib.h"

BoundingBoxComponent::BoundingBoxComponent()
    : Component("BoundingBoxComponent"), size({0, 0}), position(nullptr) {}

BoundingBoxComponent::BoundingBoxComponent(Vector2 size)
    : Component("BoundingBoxComponent"), size(size), position(nullptr) {}

void BoundingBoxComponent::init() {
  if (!entity->hasComponent<PositionComponent>())
    entity->addComponent<PositionComponent>();

  position = &entity->getComponent<PositionComponent>();
}
Vector2 BoundingBoxComponent::getSize() { return this->size;}
void BoundingBoxComponent::setSize(Vector2 size) { this->size = size; }
void BoundingBoxComponent::update(float deltaTime) {}