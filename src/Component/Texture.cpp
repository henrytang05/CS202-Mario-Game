#include "Components/Texture.h"
#include "AbstractEntity.h"
#include "Components/Position.h"

#include "raylib.h"
TextureComponent::TextureComponent() : Component("TextureComponent") {}
void TextureComponent::init() {}
void TextureComponent::update(float deltaTime) {}
void TextureComponent::drawTexture(std::string state) {
  Vector2 position = entity->getComponent<PositionComponent>().getPosition();
  DrawTexture(textures[state], position.x, position.y, WHITE);
}

void TextureComponent::addTexture(std::string state, std::string filename) {
  Texture2D texture = LoadTexture(filename.c_str());
  assert(textures.find(state) == textures.end());
  textures[state] = texture;
}
void TextureComponent::addTexture(std::string state, Texture2D texture) {
  assert(textures.find(state) == textures.end());
  textures[state] = texture;
}

Animation::Animation(float frameDelay, bool isLooping, std::string state)
    : Component("Animation"), frameDelay(frameDelay), elapsedTime(0),
      isLooping(isLooping), currentFrame(0), animationState(state),
      lastAnimationState(state) {}

void Animation::changeState(std::string state) {
  if (state != animationState) {
    lastAnimationState = animationState;
    animationState = state;
    currentFrame = 0;
  }
}

void Animation::addAnimation(std::string state,
                             std::vector<Texture2D> textures) {
  animations[state] = textures;
}
