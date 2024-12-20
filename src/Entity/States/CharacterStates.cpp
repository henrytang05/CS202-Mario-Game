#include "Entity/PlayableEntity.h"
#include "globals.h"
#include "Entity/States/CharacterStates.h"
#include "Components/SoundComponent.h"
#include "Components/Position.h"
#include "Components/Collision.h"
#include "Components/BoundingBox.h"
StandingState::StandingState(std::string size, std::string facing) : CharacterState(size, facing) {
  enumState = IDLE;
}
JumpingState::JumpingState(std::string size, std::string facing) : CharacterState(size, facing) {
  enumState = JUMPING;
}
MovingState::MovingState(std::string size, std::string facing) : CharacterState(size, facing) {
  enumState = MOVING;
}
DroppingState::DroppingState(std::string size, std::string facing) : CharacterState(size, facing) {
  enumState = DROPPING;
}
SkiddingState::SkiddingState(std::string size, std::string facing) : CharacterState(size, facing) {
  enumState = SKIDDING;
}
DucklingState::DucklingState(std::string size, std::string facing) : CharacterState(size, facing) {
  enumState = DUCKLING;
}
DeathState::DeathState(std::string size, std::string facing) : CharacterState(size, facing) {
  enumState = DEATH;
}
std::string DeathState::getState() {
  return "DEATH";
}
std::string StandingState::getState() {
  return "IDLE";
}
std::string JumpingState::getState() {
  return "JUMPING";
}
std::string MovingState::getState() {
  return "MOVING";
}
std::string DroppingState::getState() {
  return "DROPPING";
}
std::string SkiddingState::getState() {
  return "SKIDDING";
}
std::string DucklingState::getState() {
  return "DUCKLING";
}
std::string CharacterState::getCurrentState()
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
    if(enumState == DUCKLING)
        result += "DUCKLING";
    if(enumState == DEATH) 
        result += "DEATH";
    return result;
}

std::string CharacterState::getFacing() {
    return (enumFacing == LEFT ? "LEFT" : "RIGHT");
}

std::string CharacterState::getSize() {
  return (enumSize == LARGE ? "LARGE" : "SMALL");
}

void CharacterState::setFacingState(std::string newFacing) {
  if(newFacing == "LEFT") enumFacing = LEFT;
  else enumFacing = RIGHT;
}

void CharacterState::setSizeState(std::string newSize) {
  if(newSize == "LARGE") enumSize = LARGE;
  else enumSize = SMALL;
}


CharacterState::CharacterState(std::string size, std::string facing) {
  setSizeState(size);
  setFacingState(facing);
};
