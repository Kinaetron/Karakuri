#ifndef SONG_H
#define SONG_H

#include "api.h"
#include <string>

class KARAKURI_API Song
{
public:
	Song() = default;
	Song(const Song& that) = default;
	Song(Song&& that) = default;
	Song& operator=(const Song& rhs) = default;
	Song& operator=(Song&& rhs) = default;
	Song(std::string filePath);
	void Play();
	void Loop(bool loop);
	void Volume(float volume);
	void Pause();
	void Stop();
	void Destroy();


private:
	bool isLooping = false;
	float volume = 0;
};

#endif