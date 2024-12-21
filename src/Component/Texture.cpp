#include "Components/Texture.h"
#include "AbstractEntity.h"
#include "Components/Position.h"

#include "raylib.h"

Animation::Animation(float frameDelay, bool isLooping)
    : frameDelay(frameDelay), elapsedTime(0), isLooping(isLooping),
      currentFrame(0) {}

Texture2D &Animation::operator[](int index) { return frames[index]; }

TextureComponent::TextureComponent() : state(""), lastState("") {}

void TextureComponent::init() {}
void TextureComponent::update(float deltaTime) {}

void TextureComponent::drawTexture(std::string state) {
  Vector2 position = entity->getComponent<PositionComponent>().getPosition();
  Animation &animation = textures[state];
  DrawTexture(animation[animation.currentFrame], position.x, position.y, WHITE);
}

void TextureComponent::changeState(std::string state) {
  this->state = state;
  textures[state].currentFrame = 0;
}

void TextureComponent::addTexture(std::string state, std::string filename) {
  Texture2D texture = LoadTexture(filename.c_str());
  assert(textures.find(state) == textures.end());
  if (textures.size() == 0) {
    this->state = state;
    lastState = state;
  }
  Animation a;
  a.frames.push_back(texture);
  textures[state] = a;
}
void TextureComponent::addTexture(std::string state, Texture2D texture) {
  assert(textures.find(state) == textures.end());

  if (textures.size() == 0) {
    this->state = state;
    lastState = state;
  }
  Animation a;
  a.frames.push_back(texture);
  textures[state] = a;
}

void TextureComponent::addTexture(std::string state,
                                  std::vector<Texture2D> frame,
                                  float frameDelay, bool isLooping) {
  assert(this->textures.find(state) == this->textures.end());

  if (textures.size() == 0) {
    this->state = state;
    lastState = state;
  }
  Animation a(frameDelay, isLooping);
  a.frames = frame;
  this->textures[state] = a;
}

void TextureComponent::addAnimation(std::string state, Animation animation) {
  assert(this->textures.find(state) == this->textures.end());

  if (textures.size() == 0) {
    this->state = state;
    lastState = state;
  }
  this->textures[state] = animation;
}
