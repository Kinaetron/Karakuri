#include <song.h>
#include <iostream>
#include <SDL_mixer.h>
#include <spdlog/spdlog.h>

Mix_Music* song;

Song::Song(std::string filePath):
	volume(1.0f),
	isLooping(false),
	logger(nullptr)
{
	logger = spdlog::get("karakuri_logger");

	song = Mix_LoadMUS(filePath.c_str());

	if (!song)
	{
		logger->error("Song didn't load {}", SDL_GetError());
		return;
	}
}

void Song::Play() {
	Mix_PlayMusic(song, isLooping == true ? -1 : 0);
}

void Song::Loop(bool loop) {
	isLooping = loop;
}

void Song::Volume(float volume) 
{
	this->volume = volume;
	Mix_VolumeMusic(static_cast<int>(this->volume * 128.0f));
}

void Song::Pause() {
	Mix_PauseMusic();
}

void Song::Stop() {
	Mix_HaltMusic();
}

void Song::Destroy() 
{
	logger.reset();
	Mix_FreeMusic(song);
}