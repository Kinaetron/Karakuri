#include <sound_effect.h>
#include <iostream>
#include <SDL_mixer.h>

Mix_Chunk* soundEffect;

SoundEffect::SoundEffect(std::string filePath):
	isLooping(false),
	volume(1.0f),
	channel(-1)
{
	soundEffect = Mix_LoadWAV(filePath.c_str());

	if (!soundEffect)
	{
		std::cerr << "Sound Effect didn't load " << SDL_GetError() << std::endl;
		return;
	}
}

void SoundEffect::Play() 
{
	channel = Mix_GroupAvailable(-1);
	Mix_PlayChannel(channel, soundEffect, isLooping == true ? -1 : 0);
}

void SoundEffect::Loop(bool loop) {
	isLooping = loop;
}

void SoundEffect::Volume(float volume) {
	Mix_VolumeChunk(soundEffect, volume * 128);
}

void SoundEffect::Pause() {
	Mix_Paused(channel);
}

void SoundEffect::Stop() {
	Mix_HaltChannel(channel);
}

void SoundEffect::Destroy() {
	Mix_FreeChunk(soundEffect);
}