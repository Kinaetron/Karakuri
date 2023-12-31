#ifndef SONG_H
#define SONG_H

#include <memory>
#include <string>

namespace spdlog {
	class logger;
}

class Song
{
public:
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

	bool isLooping;
	float volume;
	std::shared_ptr<spdlog::logger> logger;
};

#endif