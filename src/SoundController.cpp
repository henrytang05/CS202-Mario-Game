#include "SoundController.h"

void SoundController::LoadBackgroundTracks()
{
	backgroundTracks[0] = LoadMusicStream("./assets/sounds/01. Ground Theme.wav");
	backgroundTracks[1] = LoadMusicStream("./assets/sounds/02. Underground Theme.wav");
	bg = backgroundTracks[0];
}

void SoundController::LoadSoundEffects()
{
	soundsEffects[0] = LoadSound("./assets/sounds/smb_1-up.wav");
	soundsEffects[1] = LoadSound("./assets/sounds/smb_bowserfalls.wav");
	soundsEffects[2] = LoadSound("./assets/sounds/smb_bowserfire.wav");
	soundsEffects[3] = LoadSound("./assets/sounds/smb_breakblock.wav");
	soundsEffects[4] = LoadSound("./assets/sounds/smb_bump.wav");
	soundsEffects[5] = LoadSound("./assets/sounds/smb_coin.wav");
	soundsEffects[6] = LoadSound("./assets/sounds/smb_fireball.wav");
	soundsEffects[7] = LoadSound("./assets/sounds/smb_fireworks.wav");
	soundsEffects[8] = LoadSound("./assets/sounds/smb_flagpole.wav");
	soundsEffects[9] = LoadSound("./assets/sounds/smb_gameover.wav");
	soundsEffects[10] = LoadSound("./assets/sounds/smb_jump-small.wav");
	soundsEffects[11] = LoadSound("./assets/sounds/smb_jump-super.wav");
	soundsEffects[12] = LoadSound("./assets/sounds/smb_kick.wav");
	soundsEffects[13] = LoadSound("./assets/sounds/smb_mariodie.wav");
	soundsEffects[14] = LoadSound("./assets/sounds/smb_pause.wav");
	soundsEffects[15] = LoadSound("./assets/sounds/smb_pipe.wav");
	soundsEffects[16] = LoadSound("./assets/sounds/smb_powerup.wav");
	soundsEffects[17] = LoadSound("./assets/sounds/smb_powerup_appears.wav");
	soundsEffects[18] = LoadSound("./assets/sounds/smb_stage_clear.wav");
	soundsEffects[19] = LoadSound("./assets/sounds/smb_stomp.wav");
	soundsEffects[20] = LoadSound("./assets/sounds/smb_vine.wav");
	soundsEffects[21] = LoadSound("./assets/sounds/smb_warning.wav");
	soundsEffects[22] = LoadSound("./assets/sounds/smb_world_clear.wav");
	soundsEffects[23] = LoadSound("./assets/sounds/smb_ting_sound.wav");
}

SoundController::~SoundController()
{
	for(auto& it : backgroundTracks) UnloadMusicStream(it);
	for(auto& it : soundsEffects) UnloadSound(it);
}

void SoundController::LoadSounds()
{
	LoadBackgroundTracks();
	LoadSoundEffects();
}

void SoundController::PlayGroundTheme()
{
	bg = backgroundTracks[0];
	SetMusicVolume(bg, MusicVolume);
	PlayMusicStream(bg);
}

void SoundController::PlayUndergroundTheme()
{
	bg = backgroundTracks[1];
	SetMusicVolume(bg, MusicVolume);
	PlayMusicStream(bg);
}

void SoundController::Play1upEffect()
{
	PlaySound(soundsEffects[0]);
}

void SoundController::PlayBowserFallsEffect()
{
	PlaySound(soundsEffects[1]);
}

void SoundController::PlayBowserFireEffect()
{
	PlaySound(soundsEffects[2]);
}

void SoundController::PlayBreakBlockEffect()
{
	PlaySound(soundsEffects[3]);
}

void SoundController::PlayBumpEffect()
{
	PlaySound(soundsEffects[4]);
}

void SoundController::PlayCoinEffect()
{
	PlaySound(soundsEffects[5]);
}

void SoundController::PlayFireballEffect()
{
    PlaySound(soundsEffects[6]);
}

void SoundController::PlayFireworksEffect()
{
    PlaySound(soundsEffects[7]);
}

void SoundController::PlayFlagpoleEffect()
{
    PlaySound(soundsEffects[8]);
}

void SoundController::PlayGameOverEffect()
{
    PlaySound(soundsEffects[9]);
}

void SoundController::PlayJumpSmallEffect()
{
    PlaySound(soundsEffects[10]);
}

void SoundController::PlayJumpSuperEffect()
{
    PlaySound(soundsEffects[11]);
}

void SoundController::PlayKickEffect()
{
    PlaySound(soundsEffects[12]);
}

void SoundController::PlayMarioDieEffect()
{
    PlaySound(soundsEffects[13]);
}

void SoundController::PlayPauseEffect()
{
    PlaySound(soundsEffects[14]);
}

void SoundController::PlayPipeEffect()
{
    PlaySound(soundsEffects[15]);
}

void SoundController::PlayPowerupEffect()
{
    PlaySound(soundsEffects[16]);
}

void SoundController::PlayPowerupAppearsEffect()
{
    PlaySound(soundsEffects[17]);
}

void SoundController::PlayStageClearEffect()
{
    PlaySound(soundsEffects[18]);
}

void SoundController::PlayStompEffect()
{
    PlaySound(soundsEffects[19]);
}

void SoundController::PlayVineEffect()
{
    PlaySound(soundsEffects[20]);
}

void SoundController::PlayWarningEffect()
{
    PlaySound(soundsEffects[21]);
}

void SoundController::PlayWorldClearEffect()
{
    PlaySound(soundsEffects[22]);
}

void SoundController::PlayTingSound()
{
	PlaySound(soundsEffects[23]);
}

void SoundController::Update(int time)
{
	if(time == 60) {
		SetMusicPitch(bg, 1.5);
	}
	MusicVolume = MUSIC_VOLUME;
	SoundVolume = SOUND_VOLUME;
	SetMusicVolume(bg, MusicVolume);
	for(auto& it : soundsEffects){
		SetSoundVolume(it, SoundVolume);
	}
	UpdateMusicStream(bg);
}

void SoundController::Update()
{
	Update(0);
}

void SoundController::Pause()
{
	PauseMusicStream(bg);
}
