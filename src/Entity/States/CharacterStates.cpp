#include "Entity/PlayableEntity.h"
#include "globals.h"
#include "Entity/States/CharacterStates.h"
#include "Components/SoundComponent.h"
#include "Components/Position.h"
#include "Components/Collision.h"
#include "Components/BoundingBox.h"
StandingState::StandingState(Vector2 _friction, std::string size, std::string facing, std::string state) : CharacterState(size, facing, state) {
  friction = _friction; 
}

CharacterState *StandingState::handleInput(PlayableEntity &character) {
  if(character.getComponent<CollisionComponent>().standingOn() == nullptr) {
    return new DroppingState({friction.x, GRAVITY_DEC}, getSize(), getFacing(), getState());
  }
  if (IsKeyPressed(KEY_UP)) {
    setEnumState("JUMPING");
    character.getComponent<MarioSoundComponent>().PlayJumpSmallEffect();
    if((IsKeyDown(KEY_LEFT) && getFacing() == "LEFT") || (IsKeyDown(KEY_RIGHT) && getFacing() == "RIGHT"))
      return new JumpingState((Vector2){0.0f, GRAVITY_DEC}, getSize(), getFacing(), getState());
    return new JumpingState({JUMPPING_DEC, GRAVITY_DEC}, getSize(), getFacing(), getState());
  }
  Vector2 velocity = character.getVelocity();
  if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
    if (velocity.x <= 0.0f) {
      setEnumState("MOVING");
      return new MovingState(velocity, getSize(), getFacing(), getState());
    }
    else {
      if (getFacing() == "RIGHT")
        setFacingState("LEFT");
      if (velocity.x > MAX_WALKING_VELO) {
          friction.x = SKIDDING_DEC;
          setEnumState("SKIDDING");
      }
      else {
        setEnumState("IDLE");
        return new MovingState((Vector2){-WALKING_ACC, 0.0f}, getSize(), getFacing(), getState());
      }
    }
  }
  if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)) {
    if (velocity.x >= 0.0f) {
      setEnumState("MOVING");
      return new MovingState(velocity, getSize(), getFacing(), getState());
    }
    else {
      if (getFacing() == "LEFT")
        setFacingState("RIGHT");
      if (velocity.x < -MAX_WALKING_VELO) {
        friction.x = SKIDDING_DEC;
        setEnumState("SKIDDING");
      }
      else {
        setEnumState("IDLE");
        return new MovingState((Vector2){WALKING_ACC, 0.0f}, getSize(), getFacing(), getState());
      }
    }
  }
  if (velocity.x == 0.0f)
    setEnumState("IDLE");
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

JumpingState::JumpingState(Vector2 _friction, std::string size, std::string facing, std::string state) : CharacterState(size, facing, state) {
  friction = _friction;
}

CharacterState *JumpingState::handleInput(PlayableEntity &character) {
  Vector2 velocity = character.getVelocity();
  Shared<AbstractEntity> e = character.getComponent<CollisionComponent>().collisionAbove();
  if(e != nullptr) { 
    setEnumState("DROPPING");  
    character.getComponent<PositionComponent>().setPosition((Vector2){character.getComponent<PositionComponent>().getX(), 
    e->getComponent<PositionComponent>().getY() + e->getComponent<BoundingBoxComponent>().getSize().y});
    return new DroppingState({friction.x, GRAVITY_DEC + 1.0f}, getSize(), getFacing(), getState());
  }
  if (IsKeyReleased(KEY_UP) || velocity.y <= -MAX_JUMPING_VELO || (e != nullptr))
  {
    setEnumState("DROPPING");
    return new DroppingState({friction.x, GRAVITY_DEC}, getSize(), getFacing(), getState());
  }
  setEnumState("JUMPING");
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

DroppingState::DroppingState(Vector2 _friction, std::string size, std::string facing, std::string state) : CharacterState(size, facing, state) {
  friction = _friction;
}
CharacterState *DroppingState::handleInput(PlayableEntity &character) {
  Vector2 velocity = character.getVelocity();
  Shared<AbstractEntity> e = character.getComponent<CollisionComponent>().standingOn();
  if (e) {
    setEnumState("IDLE");
    character.getComponent<PositionComponent>().setPosition((Vector2){character.getComponent<PositionComponent>().getX(), 
    e->getComponent<PositionComponent>().getY() - character.getComponent<BoundingBoxComponent>().getSize().y});
    return new StandingState({NORMAL_DEC, GRAVITY_DEC}, getSize(), getFacing(), getState());
  }
  setEnumState("DROPPING");
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

MovingState::MovingState(Vector2 _velocity, std::string size, std::string facing, std::string state) : CharacterState(size, facing, state) {
  velocity = _velocity;
  frameDelay = 10;
  frameDelayCounter = frameIndex = 0;
}

CharacterState *MovingState::handleInput(PlayableEntity &character) {
  if(character.getComponent<CollisionComponent>().standingOn() == nullptr) {
    return new DroppingState({NORMAL_DEC, GRAVITY_DEC}, getSize(), getFacing(), getState());
  }
  if (IsKeyPressed(KEY_UP)) {
    setEnumState("JUMPING");
    character.getComponent<MarioSoundComponent>().PlayJumpSmallEffect();
    return new JumpingState({0.0f, GRAVITY_DEC}, getSize(), getFacing(), getState());
  }
  if (IsKeyDown(KEY_LEFT)) {
    velocity.x -= WALKING_ACC;
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
      velocity.x -= RUNNING_ACC;
      velocity.x = std::max(velocity.x, -MAX_RUNNING_VELO);
    }
    else {
      velocity.x = std::max(velocity.x, -MAX_WALKING_VELO);
    }
  }
  if (IsKeyDown(KEY_RIGHT)) {
    velocity.x += WALKING_ACC;
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        velocity.x += RUNNING_ACC;
        velocity.x = std::min(velocity.x, MAX_RUNNING_VELO);
    }
    else {
        velocity.x = std::min(velocity.x, MAX_WALKING_VELO);
    }
  }
  if (IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_RIGHT)) {
    setEnumState("IDLE");
    return new StandingState({NORMAL_DEC, 0.0f}, getSize(), getFacing(), getState());
  }
  return nullptr;
}
void MovingState::update(PlayableEntity &character) {
  character.setVelocity(velocity);
  if ((velocity.x < 0) && (getFacing() == "RIGHT")) {
    setFacingState("LEFT");
  }
  if ((velocity.x > 0) && (getFacing() == "LEFT")) {
    setFacingState("RIGHT");
  }
  frameDelayCounter += 1;
  if (frameDelay <= frameDelayCounter) {
    frameDelayCounter = 0;
    frameIndex = (frameIndex + 1) % 2;
    if(getState() == "IDLE") setEnumState("MOVING");
    else setEnumState("IDLE");
  }
}

EnumCharacterState::EnumCharacterState(std::string _size, std::string _facing, std::string _state) {
  if(_state == "IDLE") enumState = IDLE;
  if(_state == "MOVING") enumState = MOVING;
  if(_state == "SKIDDING") enumState= SKIDDING;
  if(_state == "JUMPING") enumState = JUMPING;
  if(_state == "DROPPING") enumState = DROPPING;
  if(_facing == "LEFT") enumFacing = LEFT;
  else enumFacing = RIGHT;
  if(_size == "LARGE") enumSize = LARGE;
  else enumSize = SMALL;
}

std::string EnumCharacterState::getCurrentState()
{
    std::string result = "";
    if (enumSize == LARGE)
        result = "LARGE-";
    else
        result = "SMALL-";
    if (enumFacing == LEFT)
        result += "LEFT-";
    else
        result += "RIGHT-";
    if (enumState == IDLE)
        result += "IDLE";
    if (enumState == MOVING)
        result += "MOVING";
    if (enumState == SKIDDING)
        result += "SKIDDING";
    if (enumState == JUMPING)
        result += "JUMPING";
    if (enumState == DROPPING)
        result += "DROPPING";
    return result;
}

std::string EnumCharacterState::getFacing() {
    return (enumFacing == LEFT ? "LEFT" : "RIGHT");
}

std::string EnumCharacterState::getSize() {
  return (enumSize == LARGE ? "LARGE" : "SMALL");
}

void EnumCharacterState::setEnumState(std::string newState) {
  if(newState == "IDLE") enumState = IDLE;
  if(newState == "MOVING") enumState = MOVING;
  if(newState == "SKIDDING") enumState= SKIDDING;
  if(newState == "JUMPING") enumState = JUMPING;
  if(newState == "DROPPING") enumState = DROPPING;
}

void EnumCharacterState::setFacingState(std::string newFacing) {
  if(newFacing == "LEFT") enumFacing = LEFT;
  else enumFacing = RIGHT;
}

void EnumCharacterState::setSizeState(std::string newSize) {
  if(newSize == "LARGE") enumSize = LARGE;
  else enumSize = SMALL;
}

std::string EnumCharacterState::getState() {
  std::string result = "";
  if(enumState == IDLE) result += "IDLE";
  if(enumState == MOVING) result += "MOVING";
  if(enumState == SKIDDING) result += "SKIDDING";
  if(enumState == JUMPING) result += "JUMPING";
  if(enumState == DROPPING) result += "DROPPING";
  return result;
}

CharacterState::CharacterState(std::string size, std::string facing, std::string state) : EnumCharacterState(size, facing, state) {};
