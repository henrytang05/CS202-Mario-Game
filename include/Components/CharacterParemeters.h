#ifndef CHARACTER_PARAMETERS_COMPONENT_H
#define CHARACTER_PARAMETERS_COMPONENT_H

#include "Components/Component.h"
#include "raylib.h"

class CharacterParametersComponent : public Component {
public:
    float WALKING_ACC = 133.59375f;
    float RUNNING_ACC = 200.390625f;
    float NORMAL_DEC = 182.8125f;
    float SKIDDING_DEC = 365.625f;
    float MIN_SKIDDING = 33.75f;
    float GRAVITY_DEC = 562.0f;
    float MIN_WALKING_VELO = 4.453125f;
    float MAX_WALKING_VELO = 93.75f;
    float MAX_RUNNING_VELO = 153.75f;
    float JUMPING_VELO = -240.0f;
    float MAX_FALL = 270.0f;
    float FALL_ACC_A = 421.875f;
    float FALL_ACC = 1800.0f;
    float fallAcc;
    CharacterParametersComponent(float _WALKING_ACC,
    float _RUNNING_ACC,
    float _NORMAL_DEC,
    float _SKIDDING_DEC,
    float _MIN_SKIDDING,
    float _GRAVITY_DEC,
    float _MIN_WALKING_VELO,
    float _MAX_WALKING_VELO,
    float _MAX_RUNNING_VELO,
    float _JUMPING_VELO,
    float _MAX_FALL,
    float _FALL_ACC_A,
    float _FALL_ACC);
};

#endif // CHARACTER_PARAMETERS_COMPONENT_H
