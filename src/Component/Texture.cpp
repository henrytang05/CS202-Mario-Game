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

TextureComponent2::TextureComponent2(float frameDelay, bool isLooping,
                                     std::string animationState)
    : TextureComponent(), currentFrame(0), frameDelay(frameDelay),
      elapsedTime(0), isLooping(isLooping), animationState(animationState),
      lastAnimationState(animationState) {}

void TextureComponent2::addTexture(std::string state, std::string filename) {
  TextureComponent::addTexture(state, filename);
  animations[state].push_back(textures[state]);
  if (animations.find(animationState) == animations.end()) {
    animations[animationState] = std::vector<Texture2D>();
  }
  animations[animationState].push_back(textures[state]);
}

void TextureComponent2::addTexture(std::string state, Texture2D texture) {
  TextureComponent::addTexture(state, texture);
  animations[state].push_back(textures[state]);
  if (animations.find(animationState) == animations.end()) {
    animations[animationState] = std::vector<Texture2D>();
  }
  animations[animationState].push_back(textures[state]);
}

void TextureComponent2::changeState(std::string state) {
  if (state != animationState) {
    lastAnimationState = animationState;
    animationState = state;
    currentFrame = 0;
  }
}

void TextureComponent2::addTextures(std::string state,
                                    std::vector<Texture2D> textures) {
  if (animations.find(state) == animations.end()) {
    animations[state] = textures;
  }
  animations[state].insert(animations[state].end(), textures.begin(),
                           textures.end());
}
