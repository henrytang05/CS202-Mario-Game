#include "Entity/PlayableEntity.h"
#include "globals.h"
#include "Entity/States/CharacterStates.h"
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
std::string CharacterState::getState() {
  std::string result = "";
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
void CharacterState::setEnumState(std::string newState) {
  if (newState == "IDLE")
      enumState = IDLE;
  if (newState == "MOVING")
      enumState = MOVING;
  if (newState == "SKIDDING")
      enumState = SKIDDING;
  if (newState == "JUMPING")
      enumState = JUMPING;
  if (newState == "DROPPING")
      enumState = DROPPING;
  if (newState == "DUCKLING")
      enumState = DUCKLING;
  if (newState == "DEATH")
      enumState = DEATH;
}
void CharacterState::setSizeState(std::string newSize) {
  if(newSize == "LARGE") enumSize = LARGE;
  else enumSize = SMALL;
}


CharacterState::CharacterState(std::string state, std::string size, std::string facing) {
  setEnumState(state);
  setSizeState(size);
  setFacingState(facing);
};
