#pragma once
#include "raylib.h"
#include <array>
#include "globals.h"

class SoundController {
private:
  std::array<Music, 2> backgroundTracks;
  std::array<Sound, 24> soundsEffects;
  Music bg;
  void LoadBackgroundTracks();
  void LoadSoundEffects();
  float MusicVolume = 1.0f;
  float SoundVolume = 1.0f;
public:
  ~SoundController();
  void LoadSounds();
  void PlayGroundTheme();
  void PlayUndergroundTheme();
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
  void Update(int time);
  void Update();
};
