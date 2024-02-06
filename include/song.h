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

	/*
	* Creates a object that represents a song.
	* \param filepath, tells where the file that is being loaded up as a song.
	*/
	Song(std::string filePath);

	/*
	* Plays the song.
	*/
	void Play();

	/*
	* Sets if you want to song to loop or not, false by default.
	* \param loop, true loop song, false doesn't loop song.
	*/
	void Loop(bool loop);

	/*
	* Sets the volume of the song.
	* \param volume, goes from 0.0f to 1.0f
	*/
	void Volume(float volume);

	/*
	* Pauses the song.
	*/
	void Pause();

	/*
	* Stops the song.
	*/
	void Stop();

	/*
	* Destroys the song.
	*/
	void Destroy();


private:

	bool isLooping;
	float volume;
	std::shared_ptr<spdlog::logger> logger;
};

#endif