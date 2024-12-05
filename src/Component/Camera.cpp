#include "Components/Camera.h"
#include "Components/BoundingBox.h"
#include "Entity/Entity.h"

CameraComponent::CameraComponent() : Component() {}

void CameraComponent::init() {
  // ASSERT(entity->hasComponent<BoundingBoxComponent>());
  BoundingBoxComponent &bb = entity->getComponent<BoundingBoxComponent>();

  offset = {screenWidth / 2.0f, screenHeight / 2.0f};
  rotation = 0.0f;
  target = bb.getPos();
  zoom = 2.0f;
}

void CameraComponent::setTarget(Vector2 target) { this->target = target; }

void CameraComponent::update() {
  setTarget(entity->getComponent<BoundingBoxComponent>().getPos());
}
