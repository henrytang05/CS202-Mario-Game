#include "Components/Camera.h"
#include "Components/BoundingBox.h"
#include "Entity/Entity.h"

CameraComponent::CameraComponent() : Component("CameraComponent") {}

void CameraComponent::init() {
  if (!entity->hasComponent<BoundingBoxComponent>())
    entity->addComponent<BoundingBoxComponent>();

  // BoundingBoxComponent &bb = entity->getComponent<BoundingBoxComponent>();
  offset = {screenWidth / 2.0f, screenHeight / 2.0f};
  rotation = 0.0f;
  // target = bb.getPos();
  zoom = 2.0f;

#ifdef _DEBUG
  Log("log.txt", LogLevel::INFO, name + " created");
#endif
}

void CameraComponent::setTarget(Vector2 target) { this->target = target; }

void CameraComponent::update() {
  setTarget(entity->getComponent<BoundingBoxComponent>().getPos());
}

void CameraComponent::setTarget(Entity &target) {
  this->target = target.getComponent<BoundingBoxComponent>().getPos();
}
