#pragma once
#include <array>
#include "raylib.h"

class SoundController
{
private:
<<<<<<< Updated upstream
	std::array<Music, 2> backgroundTracks;
	std::array<Sound, 23> soundsEffects;
	Music bg;
	void LoadBackgroundTracks();
	void LoadSoundEffects();
	float volume = 1.0f;
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
	void Update();
=======
  std::array<Music, 2> backgroundTracks;
  std::array<Sound, 24> soundsEffects;
  Music bg;
  void LoadBackgroundTracks();
  void LoadSoundEffects();
  float volume = 1.0f;

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
  void Update();
>>>>>>> Stashed changes
};
