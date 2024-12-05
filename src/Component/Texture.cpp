#include "Components/Texture.h"
#include "Components/Position.h"
#include "Entity/Entity.h"

TextureComponent::TextureComponent(std::string filename, int _numFrame)
    : Component() {
  numFrame = _numFrame;
  texture = LoadTexture((filename + ".png").c_str());
  flipTexture = LoadTexture((filename + "-Flip.png").c_str());
  isFlip = 0;
  frameWidth = texture.width / numFrame;
  frameRec = {(float)frameWidth, 0.0f, (float)frameWidth,
              (float)texture.height};
}

void TextureComponent::init() {}

void TextureComponent::update() {
  PositionComponent &position = entity->getComponent<PositionComponent>();

  drawTexture(position.getPos());
}

bool TextureComponent::getIsFlip() { return isFlip; }
void TextureComponent::updateFlip() { isFlip ^= 1; }
void TextureComponent::drawTexture(Vector2 position) {
  if (isFlip) {
    DrawTextureRec(flipTexture, frameRec, position, WHITE);
  } else {
    DrawTextureRec(texture, frameRec, position, WHITE);
  }
  DrawLine(position.x, position.y, position.x + 16, position.y, BLACK);
  DrawLine(position.x, position.y + 23, position.x + 16, position.y + 23,
           BLACK);
  DrawLine(position.x, position.y, position.x, position.y + 23, BLACK);
  DrawLine(position.x + 16, position.y, position.x + 16, position.y + 23,
           BLACK);
}
void TextureComponent::updateFrame(int frameIndex) {
  if (isFlip) {
    frameRec.x = float(frameWidth * (numFrame - frameIndex - 1));
  } else
    frameRec.x = float(frameWidth * frameIndex);
}
