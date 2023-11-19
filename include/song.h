#ifndef SONG_H
#define SONG_H

#include "api.h"
#include <string>

class KARAKURI_API Song
{
public:
	Song(std::string filePath);
	void Play();
	void Loop(bool loop);
	void Volume(float volume);
	void Pause();
	void Stop();
	void Destroy();


private:
	bool isLooping;
	float volume;
};

#endif