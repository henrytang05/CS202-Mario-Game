#include "Components/Transform.h"

#include "Components/Position.h"
#include "Entity/Entity.h"
#include "globals.h"
#include "pch.h"

TransformComponent::TransformComponent(Vector2 velocity, float speed, Entity *e)
    : Component(e), velocity(velocity), speed(speed) {
  init();

#ifdef _DEBUG
  Log("log.txt", LogLevel::INFO, name + " created");
#endif
}

void TransformComponent::init() {
  ASSERT(entity->hasComponent<PositionComponent>());
  name = "TransformComponent";
}

void TransformComponent::update() {
  PositionComponent &position = entity->getComponent<PositionComponent>();
  position.setPos(position.getPos() + velocity);
}
