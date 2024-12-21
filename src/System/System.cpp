#include "System/System.h"

#include "AbstractEntity.h"
#include "Components/BoundingBox.h"
#include "Components/Collision.h"
#include "Components/Components_include.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "globals.h"
#include "raylib.h"

void TransformSystem::update(Shared<AbstractEntity> entity, float dt) {
  if (!entity->hasAllComponents<PositionComponent, TransformComponent>()) {
    throw std::runtime_error(
        "Entity does not have required components for PhysicSystem");
  }

  auto &position = entity->getComponent<PositionComponent>();
  auto &transform = entity->getComponent<TransformComponent>();

  float x = position.getX() + transform.getVelocity().x * dt;
  float y = position.getY() + transform.getVelocity().y * dt;
  position.setPosition({x, y});
}

void AnimationSystem::update(Shared<AbstractEntity> entity, float dt) {
  if (!entity->isActive())
    return;
  if (!entity->hasAllComponents<Animation, PositionComponent,
                                BoundingBoxComponent>()) {
    throw std::runtime_error(
        "Entity does not have required components for RenderSystem");
  }

  auto &position = entity->getComponent<PositionComponent>();
  auto &texture = entity->getComponent<Animation>();
  auto &frames = texture.animations[texture.animationState];
  if (frames.empty()) {
    throw std::runtime_error("No frames in animation");
  }

  texture.elapsedTime += dt;
  while (texture.elapsedTime >= texture.frameDelay) {
    texture.elapsedTime -= texture.frameDelay;
    texture.currentFrame++;
    if (texture.currentFrame >= frames.size()) {
      texture.currentFrame = texture.isLooping ? 0 : frames.size() - 1;
    }
  }

  Texture2D choosen_texture = frames[texture.currentFrame];
  DrawTexture(choosen_texture, position.getX(), position.getY(), WHITE);
}
