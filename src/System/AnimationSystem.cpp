#include "Components/Components_include.h"
#include "System/System.h"

void AnimationSystem::draw(float dt) {
  EntityManager &EM = EntityManager::getInstance();
  auto Entities = EM.getHasAll<TextureComponent, PositionComponent>();
  for (auto tEntity : Entities) {
    if (tEntity.expired())
      throw std::runtime_error("Entity is expired");
    auto entity = tEntity.lock();
    entity->changeState();

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
    if(animation.elapsedTime >= animation.frameDelay) {     
      if(texture.state == "Die") {
        EM.removeComponent<TextureComponent>(entity);    
        continue;
      }
    }
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
