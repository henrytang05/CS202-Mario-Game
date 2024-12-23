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
  if (!entity->hasAllComponents<TextureComponent, PositionComponent
                            >()) {
    throw std::runtime_error(
        "Entity does not have required components for RenderSystem");
  }

  auto &position = entity->getComponent<PositionComponent>();
  auto &texture = entity->getComponent<TextureComponent>();
  auto &animation = texture.textures[texture.state];
  auto &frames = animation.frames;
  if (frames.empty()) {
    throw std::runtime_error("No frames in animation");
  }

  animation.elapsedTime += dt;
  if (!entity->isActive() && animation.elapsedTime >= animation.frameDelay)
    return;

  while (animation.elapsedTime >= animation.frameDelay) {
    animation.elapsedTime -= animation.frameDelay;
    animation.currentFrame++;
    if (animation.currentFrame >= frames.size()) {
      animation.currentFrame = animation.isLooping ? 0 : frames.size() - 1;
    }
  }

  Texture2D choosen_texture = frames[animation.currentFrame];
  DrawTexture(choosen_texture, position.getX(), position.getY(), WHITE);
}
