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
  if (!entity->hasAllComponents<TextureComponent2, PositionComponent,
                                BoundingBoxComponent>()) {
    throw std::runtime_error(
        "Entity does not have required components for RenderSystem");
  }

  auto &texture = entity->getComponent<TextureComponent2>();
  auto &position = entity->getComponent<PositionComponent>();

  auto &frames = texture.animations[texture.animationState];
  texture.elapsedTime += dt;
  if (texture.elapsedTime >= texture.frameDelay) {
    texture.elapsedTime -= texture.frameDelay;
    if (!frames.empty()) {
      texture.currentFrame++;
      if (texture.currentFrame >= frames.size()) {
        if (texture.isLooping) {
          texture.currentFrame = 0;
        } else {
          texture.currentFrame = frames.size() - 1;
        }
      }
    }
  }
  Texture2D choosen_texture = frames[texture.currentFrame];
  DrawTexture(choosen_texture, position.getX(), position.getY(), WHITE);
}
