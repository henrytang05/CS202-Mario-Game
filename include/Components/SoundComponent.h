#pragma once
#include "Component.h"
#include <array>
#include "raylib.h"

class MarioSoundComponent : public Component {
    private:
    std::array<Sound, 24> soundsEffects;
    public:
    MarioSoundComponent();
    void init() override {};
    void LoadSounds();
    void Play1upEffect();
    void PlayBowserFallsEffect();
    void PlayBowserFireEffect();
    void PlayBreakBlockEffect();
    void PlayBumpEffect();
    void PlayCoinEffect();
    void PlayFireballEffect();
    void PlayFireworksEffect();
    void PlayFlagpoleEffect();
    void PlayGameOverEffect();
    void PlayJumpSmallEffect();
    void PlayJumpSuperEffect();
    void PlayKickEffect();
    void PlayMarioDieEffect();
    void PlayPauseEffect();
    void PlayPipeEffect();
    void PlayPowerupEffect();
    void PlayPowerupAppearsEffect();
    void PlayStageClearEffect();
    void PlayStompEffect();
    void PlayVineEffect();
    void PlayWarningEffect();
    void PlayWorldClearEffect();
    void PlayTingSound();
};