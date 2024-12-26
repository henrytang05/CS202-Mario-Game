#include "Components/CharacterParemeters.h"

CharacterParametersComponent::CharacterParametersComponent(float _WALKING_ACC, float _RUNNING_ACC, float _NORMAL_DEC, float _SKIDDING_DEC, float _MIN_SKIDDING, float _GRAVITY_DEC, float _MIN_WALKING_VELO, float _MAX_WALKING_VELO, float _MAX_RUNNING_VELO, float _JUMPING_VELO, float _MAX_FALL, float _FALL_ACC_A, float _FALL_ACC) : Component("CharacterParametersComponent") {
    WALKING_ACC = _WALKING_ACC;
    RUNNING_ACC = _RUNNING_ACC;
    NORMAL_DEC = _NORMAL_DEC;
    SKIDDING_DEC = _SKIDDING_DEC;
    MIN_SKIDDING = _MIN_SKIDDING;
    GRAVITY_DEC = _GRAVITY_DEC;
    MIN_WALKING_VELO = _MIN_WALKING_VELO;
    MAX_WALKING_VELO = _MAX_WALKING_VELO;
    MAX_RUNNING_VELO = _MAX_RUNNING_VELO;
    JUMPING_VELO = _JUMPING_VELO;
    MAX_FALL = _MAX_FALL;
    FALL_ACC_A = _FALL_ACC_A;
    FALL_ACC = _FALL_ACC;
    fallAcc = GRAVITY_DEC;
}