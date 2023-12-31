#ifndef SOUND_EFFECT_H
#define SOUND_EFFECT_H

#include <memory>
#include <string>

namespace spdlog {
	class logger;
}

class SoundEffect
{
public:
	SoundEffect(const SoundEffect& that) = default;
	SoundEffect(SoundEffect&& that) = default;
	SoundEffect& operator=(const SoundEffect& rhs) = default;
	SoundEffect& operator=(SoundEffect&& rhs) = default;
	SoundEffect(const std::string& filePath);
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
	std::shared_ptr<spdlog::logger> logger;
};
#endif