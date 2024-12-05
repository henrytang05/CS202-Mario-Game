#ifndef CHARACTER_NEW_H
#define CHARACTER_NEW_H

#include "CharacterState.h"
#include "Entity/Entity.h"

class newCharacter : public Entity {
public:
  newCharacter(std::string name)
      : Entity(name), stateCharacter(new StandingState({0.0f, 0.0f})) {}

protected:
  Unique<CharacterState> stateCharacter;
};

#endif // CHARACTER_NEW_H
