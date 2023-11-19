#ifndef SOUND_EFFECT_H
#define SOUND_EFFECT_H

#include "api.h"
#include <string>

class KARAKURI_API SoundEffect
{
public:
	SoundEffect(std::string filePath);
	void Play();
	void Loop(bool loop);
	void Volume(float volume);
	void Pause();
	void Stop();
	void Destroy();

private:
	int channel;
	float volume;
	bool isLooping;
};
#endif