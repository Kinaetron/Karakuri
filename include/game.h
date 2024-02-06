#ifndef GAME_H
#define GAME_H

#include <string>
#include <cstdint>
#include "graphics_device.h"
#include <memory>

namespace spdlog {
    class logger;
}

class Game
{
public:
	Game(const Game& that) = default;
	Game(Game&& that) = default;
	Game& operator=(const Game& rhs) = default;

	/*
	* This is the point of entry for using the engine.
	* 
	* \param title sets the name of the game window.
	* \param width sets the width of the game window.
	* \param height sets the height of the game window.
	* \param scale sets the scale of the window. It scales up the window size by that scale will keeping the resolution the same.
	*/
	Game(const std::string& title, int width, int height, int scale);

	/*
	* This method is here to create objects and deal with settings. It is only called once in the run of the game. 
	*/
	virtual void Initialize();

	/*
	* This method is where physics need to be updated. It's called 60 times a second.
	*/
	virtual void Update();

	/*
	* This method is where objects are drawn. By default it is called at the same refresh limit as the monitor the game is running on.
	*/
	virtual void Draw();

	/*
	*This method is the first method you call after creating creating the game object. It starts the game runs the game loop.
	*/
	void Run();

	/*
	* This method destroys all the objects used by the game by default. Call it when you're closing the game.
	*/
	void Quit();

	/*
	* This method returns how many milliseconds have passed since the last call. This should be about 16.67.
	*/
	const float MilliSecondsPerUpdate() const { return target_milliseconds_per_update; }

	GraphicsDevice graphicsDevice;

private:
	bool isRunning = true;
	void ProcessEvents();
	const float target_milliseconds_per_update;
	std::shared_ptr<spdlog::logger> logger;
};
#endif