#include "Components/Texture.h"
#include "AbstractEntity.h"
#include "Components/Position.h"
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
