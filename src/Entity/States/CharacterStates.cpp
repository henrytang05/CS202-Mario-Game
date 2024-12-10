#include "Entity/PlayableEntity.h"

#include "Components/Texture.h"
#include "Entity/States/CharacterStates.h"
StandingState::StandingState(Vector2 _friction) { friction = _friction; }

CharacterState *StandingState::handleInput(PlayableEntity &character) {
  TextureComponent &texture = character.getComponent<TextureComponent>();
  if (IsKeyDown(KEY_UP)) {
    texture.updateFrame(4);
    if(!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT))
      return new JumpingState({JUMPPING_DEC, GRAVITY_DEC});
    return new JumpingState({0.0f, GRAVITY_DEC});
  }
  Vector2 velocity = character.getVelocity();
  if(IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
    if(velocity.x <= 0.0f) {
      return new MovingState(velocity);
    }
    else {  
      if(character.getComponent<TextureComponent>().getIsFlip() == false )
        character.getComponent<TextureComponent>().updateFlip();
      if(velocity.x > MAX_WALKING_VELO) {
        friction.x = SKIDDING_DEC;
        character.getComponent<TextureComponent>().updateFrame(2);
      }
      else {
        character.getComponent<TextureComponent>().updateFrame(0);
        return new MovingState((Vector2){-WALKING_ACC, 0.0f});
      }
    }
  }
  if(IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)) {
    if(velocity.x >= 0.0f) {
      return new MovingState(velocity);
    }
    else {
      if(character.getComponent<TextureComponent>().getIsFlip() == true)
        character.getComponent<TextureComponent>().updateFlip();
      if(velocity.x < -MAX_WALKING_VELO) {
        friction.x = SKIDDING_DEC;
        character.getComponent<TextureComponent>().updateFrame(2);
      }
      else {
        character.getComponent<TextureComponent>().updateFrame(0);
        return new MovingState((Vector2){WALKING_ACC, 0.0f});
      }
    }
  }
  if (velocity.x == 0.0f) 
    texture.updateFrame(0);
  return nullptr;
}

void StandingState::update(PlayableEntity &character) {
  Vector2 velocity = character.getVelocity();
  velocity.y = 0.0f;
  if (velocity.x < 0)
    velocity.x = std::min(velocity.x + friction.x, 0.0f);
  if (velocity.x > 0)
    velocity.x = std::max(velocity.x - friction.x, 0.0f);
  character.setVelocity(velocity);
}

JumpingState::JumpingState(Vector2 _friction) { friction = _friction; }
 
CharacterState *JumpingState::handleInput(PlayableEntity &character) {
  Vector2 velocity = character.getVelocity();
  TextureComponent &texture = character.getComponent<TextureComponent>();
  if (IsKeyReleased(KEY_UP) || velocity.y <= -MAX_JUMPING_VELO) {
    texture.updateFrame(5);
    return new DroppingState({friction.x, GRAVITY_DEC});
  }
  texture.updateFrame(4);
  return nullptr;
}
void JumpingState::update(PlayableEntity &character) {
  Vector2 velocity = character.getVelocity();
  if (velocity.x < 0) 
    velocity.x = std::min(velocity.x + friction.x, 0.0f);
  if (velocity.x > 0)
    velocity.x = std::max(velocity.x - friction.x, 0.0f);
  velocity.y = std::max(velocity.y - JUMPING_ACC, -MAX_JUMPING_VELO);
  character.setVelocity(velocity);
}  

DroppingState::DroppingState(Vector2 _friction) { friction = _friction; }
CharacterState *DroppingState::handleInput(PlayableEntity &character) {
  TextureComponent &texture = character.getComponent<TextureComponent>();
  Vector2 velocity = character.getVelocity();
  if (character.isOnTheGround()) {
    texture.updateFrame(0);
    return new StandingState({NORMAL_DEC, 0.0f});
  }
  texture.updateFrame(5);
  return nullptr;
}
void DroppingState::update(PlayableEntity &character) {
  Vector2 velocity = character.getVelocity();
  if (velocity.x < 0)
    velocity.x = std::min(velocity.x + friction.x, 0.0f);
  if (velocity.x > 0)
    velocity.x = std::max(velocity.x - friction.x, 0.0f);
  velocity.y = std::min(velocity.y + friction.y, MAX_JUMPING_VELO);
  character.setVelocity(velocity);
}

MovingState::MovingState(Vector2 _velocity) {
  velocity = _velocity;
  frameDelay = 10;
  frameDelayCounter = frameIndex = 0;
}

CharacterState *MovingState::handleInput(PlayableEntity &character) {
  TextureComponent &texture = character.getComponent<TextureComponent>();
  if (IsKeyDown(KEY_UP)) {
    texture.updateFrame(4);
    return new JumpingState({0.0f, GRAVITY_DEC});
  }
  if (IsKeyDown(KEY_LEFT)) {
    velocity.x -= WALKING_ACC;
    if(IsKeyDown(KEY_LEFT_SHIFT)) {
      velocity.x -= RUNNING_ACC;
      velocity.x = std::max(velocity.x, -MAX_RUNNING_VELO);
    }
    else {
      velocity.x = std::max(velocity.x, -MAX_WALKING_VELO);
    }
  }
  if (IsKeyDown(KEY_RIGHT)) {
    velocity.x += WALKING_ACC;
    if(IsKeyDown(KEY_LEFT_SHIFT)) {
      velocity.x += RUNNING_ACC;
      velocity.x = std::min(velocity.x, MAX_RUNNING_VELO);
    }
    else {
      velocity.x = std::min(velocity.x, MAX_WALKING_VELO);
    }
  }
  if (IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_RIGHT)) {
    return new StandingState({NORMAL_DEC, 0.0f});
  }
  return nullptr;
}
void MovingState::update(PlayableEntity &character) {
  TextureComponent &texture = character.getComponent<TextureComponent>();
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