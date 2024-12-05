#include "Components/BoundingBox.h"
#include "Components/Position.h"
#include "Entity/Entity.h"

BoundingBoxComponent::BoundingBoxComponent(Entity *e) : Component(e) {
  init();
#ifdef _DEBUG
  Log("log.txt", LogLevel::INFO, name + " created");
#endif
}

void BoundingBoxComponent::init() {
  ASSERT(entity->hasComponent<PositionComponent>());

  position = std::make_shared<PositionComponent>(
      entity->getComponent<PositionComponent>());
  size = {0, 0};
  name = "BoundingBoxComponent";
}

void BoundingBoxComponent::setSize(Vector2 size) { this->size = size; }

Vector2 BoundingBoxComponent::getPos() { return position->getPos(); }

float BoundingBoxComponent::getX() const { return position->getX(); }
float BoundingBoxComponent::getY() const { return position->getY(); }
void BoundingBoxComponent::setX(float x) { position->setX(x); }
void BoundingBoxComponent::setY(float y) { position->setY(y); }

void BoundingBoxComponent::update() {
  if (position->getX() <= 0)
    position->setX(0.0f);
  if (position->getX() + size.x >= screenWidth)
    position->setX(screenWidth - size.x);
  if (position->getY() + size.y >= ground)
    position->setY(ground - size.y);
}
