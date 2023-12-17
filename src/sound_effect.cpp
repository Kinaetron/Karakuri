#include <sound_effect.h>
#include <SDL_mixer.h>
#include <spdlog/spdlog.h>

Mix_Chunk* soundEffect;

SoundEffect::SoundEffect(const std::string& filePath):
	isLooping(false),
	volume(1.0f),
	channel(-1),
	logger(nullptr)
{
	logger = spdlog::get("karakuri_logger");

	soundEffect = Mix_LoadWAV(filePath.c_str());

	if (!soundEffect)
	{
		logger->error("Sound Effect didn't load: {}", SDL_GetError());
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
	Mix_VolumeChunk(soundEffect, static_cast<int>(volume * 128.0f));
}

void SoundEffect::Pause() {
	Mix_Paused(channel);
}

void SoundEffect::Stop() {
	Mix_HaltChannel(channel);
}

void SoundEffect::Destroy() 
{
	logger.reset();
	Mix_FreeChunk(soundEffect);
}