#include "Components/SoundComponent.h"
#include "globals.h"

MarioSoundComponent::MarioSoundComponent() : Component("SoundComponent") {}
void MarioSoundComponent::LoadSounds()
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

	for(auto& it : soundsEffects){
		SetSoundVolume(it, SOUND_VOLUME);
	}
}

void MarioSoundComponent::Play1upEffect()
{
	PlaySound(soundsEffects[0]);
}

void MarioSoundComponent::PlayBowserFallsEffect()
{
	PlaySound(soundsEffects[1]);
}

void MarioSoundComponent::PlayBowserFireEffect()
{
	PlaySound(soundsEffects[2]);
}

void MarioSoundComponent::PlayBreakBlockEffect()
{
	PlaySound(soundsEffects[3]);
}

void MarioSoundComponent::PlayBumpEffect()
{
	PlaySound(soundsEffects[4]);
}

void MarioSoundComponent::PlayCoinEffect()
{
	PlaySound(soundsEffects[5]);
}

void MarioSoundComponent::PlayFireballEffect()
{
    PlaySound(soundsEffects[6]);
}

void MarioSoundComponent::PlayFireworksEffect()
{
    PlaySound(soundsEffects[7]);
}

void MarioSoundComponent::PlayFlagpoleEffect()
{
    PlaySound(soundsEffects[8]);
}

void MarioSoundComponent::PlayGameOverEffect()
{
    PlaySound(soundsEffects[9]);
}

void MarioSoundComponent::PlayJumpSmallEffect()
{
    PlaySound(soundsEffects[10]);
}

void MarioSoundComponent::PlayJumpSuperEffect()
{
    PlaySound(soundsEffects[11]);
}

void MarioSoundComponent::PlayKickEffect()
{
    PlaySound(soundsEffects[12]);
}

void MarioSoundComponent::PlayMarioDieEffect()
{
    PlaySound(soundsEffects[13]);
}

void MarioSoundComponent::PlayPauseEffect()
{
    PlaySound(soundsEffects[14]);
}

void MarioSoundComponent::PlayPipeEffect()
{
    PlaySound(soundsEffects[15]);
}

void MarioSoundComponent::PlayPowerupEffect()
{
    PlaySound(soundsEffects[16]);
}

void MarioSoundComponent::PlayPowerupAppearsEffect()
{
    PlaySound(soundsEffects[17]);
}

void MarioSoundComponent::PlayStageClearEffect()
{
    PlaySound(soundsEffects[18]);
}

void MarioSoundComponent::PlayStompEffect()
{
    PlaySound(soundsEffects[19]);
}

void MarioSoundComponent::PlayVineEffect()
{
    PlaySound(soundsEffects[20]);
}

void MarioSoundComponent::PlayWarningEffect()
{
    PlaySound(soundsEffects[21]);
}

void MarioSoundComponent::PlayWorldClearEffect()
{
    PlaySound(soundsEffects[22]);
}

void MarioSoundComponent::PlayTingSound()
{
	PlaySound(soundsEffects[23]);
}