#include "Entity/PlayableEntity.h"

#include "Components/Texture.h"
NewStandingState::NewStandingState(Vector2 _fraction) { fraction = _fraction; }

NewCharacterState *NewStandingState::handleInput(PlayableEntity &character) {
  TextureComponent &texture = character.getComponent<TextureComponent>();
  if (IsKeyDown(KEY_UP)) {
    texture.updateFrame(4);
    return new NewJumpingState({0.0f, 0.0f});
  }
  Vector2 velocity = character.getVelocity();
  if (IsKeyDown(KEY_LEFT)) {
    if (velocity.x == 0)
      return new NewMovingState({-2.0f, 0.0f});
    else {
      if (texture.getIsFlip() == false) {
        texture.updateFlip();
        texture.updateFrame(2);
      }
    }
  }
  if (IsKeyDown(KEY_RIGHT)) {
    if (velocity.x == 0)
      return new NewMovingState({2.0f, 0.0f});
    else {
      if (texture.getIsFlip() == true) {
        texture.updateFlip();
        texture.updateFrame(2);
      }
    }
  }
  if (velocity.x == 0.0f)
    texture.updateFrame(0);
  return nullptr;
}

void NewStandingState::update(PlayableEntity &character) {
  Vector2 velocity = character.getVelocity();
  velocity.y = 0.0f;
  if (velocity.x < 0)
    velocity.x = std::min(velocity.x + fraction.x, 0.0f);
  if (velocity.x > 0)
    velocity.x = std::max(velocity.x - fraction.x, 0.0f);
  character.setVelocity(velocity);
}

NewJumpingState::NewJumpingState(Vector2 _fraction) { fraction = _fraction; }

NewCharacterState *NewJumpingState::handleInput(PlayableEntity &character) {
  Vector2 velocity = character.getVelocity();
  TextureComponent &texture = character.getComponent<TextureComponent>();
  if (IsKeyReleased(KEY_UP) || velocity.y <= -15.0f) {
    texture.updateFrame(5);
    return new NewDroppingState({0.21f, 1.0f});
  }
  texture.updateFrame(4);
  return nullptr;
}
void NewJumpingState::update(PlayableEntity &character) {
  Vector2 velocity = character.getVelocity();
  velocity.y = std::max(velocity.y - 2.0f, -15.0f);
  if (velocity.x < 0)
    velocity.x = std::min(velocity.x + fraction.x, 0.0f);
  if (velocity.x > 0)
    velocity.x = std::max(velocity.x - fraction.x, 0.0f);
  character.setVelocity(velocity);
}

NewDroppingState::NewDroppingState(Vector2 _fraction) { fraction = _fraction; }
NewCharacterState *NewDroppingState::handleInput(PlayableEntity &character) {
  TextureComponent &texture = character.getComponent<TextureComponent>();
  if (character.isOnTheGround()) {
    texture.updateFrame(0);
    return new NewStandingState(fraction);
  }
  texture.updateFrame(5);
  return nullptr;
}
void NewDroppingState::update(PlayableEntity &character) {
  Vector2 velocity = character.getVelocity();
  velocity.y = std::min(velocity.y + fraction.y, 15.0f);
  if (velocity.x < 0)
    velocity.x = std::min(velocity.x + fraction.x, 0.0f);
  if (velocity.x > 0)
    velocity.x = std::max(velocity.x - fraction.x, 0.0f);
  character.setVelocity(velocity);
}

NewMovingState::NewMovingState(Vector2 _velocity) {
  velocity = _velocity;
  frameDelay = 10;
  frameDelayCounter = frameIndex = 0;
}

NewCharacterState *NewMovingState::handleInput(PlayableEntity &character) {
  TextureComponent &texture = character.getComponent<TextureComponent>();
  if (IsKeyDown(KEY_UP)) {
    texture.updateFrame(4);
    return new NewJumpingState({0.1f, 0.0f});
  }
  if (IsKeyDown(KEY_LEFT)) {
    velocity.x -= 2.0f;
  }
  if (IsKeyDown(KEY_RIGHT)) {
    velocity.x += 2.0f;
  }
  if (IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_RIGHT)) {
    return new NewStandingState({0.5f, 0.0f});
  }
  return nullptr;
}
void NewMovingState::update(PlayableEntity &character) {
  TextureComponent &texture = character.getComponent<TextureComponent>();
  velocity.x = std::min(velocity.x, 10.0f);
  velocity.x = std::max(velocity.x, -10.0f);
  character.setVelocity(velocity);
  if ((velocity.x < 0) && (texture.getIsFlip() == false)) {
    texture.updateFlip();
    texture.updateFrame(frameIndex);
  }
  if ((velocity.x > 0) && (texture.getIsFlip() == true)) {
    texture.updateFlip();
    texture.updateFrame(frameIndex);
  }
  frameDelayCounter += 1;
  if (frameDelay <= frameDelayCounter) {
    frameDelayCounter = 0;
    frameIndex = (frameIndex + 1) % 2;
    texture.updateFrame(frameIndex);
  }
}
