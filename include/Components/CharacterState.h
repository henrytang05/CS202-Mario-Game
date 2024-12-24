#ifndef CHARACTER_STATE_COMPONENT_H
#define CHARACTER_STATE_COMPONENT_H

#include "Components/Component.h"
#include "Entity/States/CharacterStates.h"
#include "raylib.h"

class CharacterStateComponent : public Component, public CharacterState {
public:
  CharacterStateComponent();
};

#endif // CHARACTER_STATE_COMPONENT_H
