#include "System/System.h"

#include "AbstractEntity.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "EntityManager.h"
#include "globals.h"
#include "raylib.h"

void TransformSystem::update(EntityManager &EM, float dt) {
  auto Entities = EM.getHasAll<PositionComponent, TransformComponent>();

  for (auto entity : Entities) {
    auto &position = EM.getComponent<PositionComponent>(entity);
    auto &transform = EM.getComponent<TransformComponent>(entity);

    float x = position.x + transform.x * dt;
    float y = position.y + transform.y * dt;
    position.setPosition({x, y});
  }
}

void AnimationSystem::update(EntityManager &EM, float dt) {
  auto Entities = EM.getHasAll<TextureComponent, PositionComponent>();
  for (auto entity : Entities) {
    auto &position = EM.getComponent<PositionComponent>(entity);
    auto &texture = EM.getComponent<TextureComponent>(entity);
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
    DrawTexture(choosen_texture, position.x, position.y, WHITE);
  }
}
