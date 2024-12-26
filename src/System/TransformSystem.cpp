#include "Components/Components_include.h"
#include "System/System.h"

void TransformSystem::update(float dt) {
  EntityManager &EM = EntityManager::getInstance();
  auto Entities = EM.getHasAll<PositionComponent, TransformComponent>();

  for (auto tEntity : Entities) {
    if (tEntity.expired())
      throw std::runtime_error("Entity is expired");
    auto entity = tEntity.lock();
    entity->update(dt);

    auto &position = entity->getComponent<PositionComponent>();
    auto &transform = entity->getComponent<TransformComponent>();

    float x = position.x + transform.x * dt;
    float y = position.y + transform.y * dt;
    position.setPosition({x, y});
  }
}

void SwingSystem::update(float dt) {
  EntityManager &EM = EntityManager::getInstance();
  auto Entities = EM.getHasAll<SwingComponent, PositionComponent>();
  for (auto tEntity : Entities) {
    if (tEntity.expired())
      throw std::runtime_error("Entity is expired");
    if(tEntity.lock()->isActive() == false) continue;
    auto entity = tEntity.lock();
    auto &position = EM.getComponent<PositionComponent>(entity);
    auto &swing = EM.getComponent<SwingComponent>(entity);
    float amplitude = 30.0f; // Distance to move up and down
    float frequency = 1.0f;  // Speed of oscillation
    swing.elapsedTime += dt;
    Vector2 position_change = position.getPosition();
    position_change.y =
        swing.position_fixed.y -
        amplitude * (1.0f + sin(frequency * swing.elapsedTime)) / 2.0f;
    if (position_change.y > swing.position_fixed.y) {
      position_change.y = swing.position_fixed.y;
    }
    position.setPosition(position_change);
  }
}
