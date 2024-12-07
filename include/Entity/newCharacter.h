#ifndef CHARACTER_NEW_H
#define CHARACTER_NEW_H

#include "CharacterStates.h"
#include "Components/Camera.h"
#include "Entity/Entity.h"

class newCharacter : public Entity {
public:
  newCharacter(std::string name)
      : Entity(name), stateCharacter(new NewStandingState({0.0f, 0.0f})) {}
  void update() override {
    NewCharacterState *newState = stateCharacter->handleInput(*this);
    if (newState) {
      delete stateCharacter;
      stateCharacter = newState;
    }
    stateCharacter->update(*this);
    for (auto &c : components) {
      c->update();
    }
    Vector2 position = getComponent<PositionComponent>().getPos();
    getComponent<CameraComponent>().setTarget(position);
  }

protected:
  NewCharacterState *stateCharacter;
};

#endif // CHARACTER_NEW_H
