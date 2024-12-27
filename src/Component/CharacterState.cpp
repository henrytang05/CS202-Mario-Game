#include "Components/CharacterState.h"

CharacterStateComponent::CharacterStateComponent()
    : Component("CharacterStateComponent"),
      CharacterState("DROPPING", "SMALL", "RIGHT") {};

void CharacterStateComponent::to_json(json &j) const { j = *this; }
