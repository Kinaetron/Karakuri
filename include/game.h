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
	const float MilliSecondsPerUpdate() const { return fixed_deltatime * 1000; }

	/*
	* This method pauses the game for the amount of milliseconds you specify with timeToStop.
	*/
	static void Pause(float timeToStop);

	std::shared_ptr<GraphicsDevice>& GameGraphicsDevice() { return gameGraphicsDevice; };

private:
	const double update_rate = 60;
	bool isRunning = true;
	bool resync = true;
	void ProcessEvents();
	std::shared_ptr<spdlog::logger> logger;

	double fixed_deltatime = 0;
	int64_t clocks_per_second = 0;
	int64_t desired_frametime = 0;
	int64_t vsync_maxerror = 0;
	int display_framerate = 60;
	int64_t snap_hz = 0;
	int64_t snap_frequencies[8] = {};
	int64_t time_averager[4] = {};
	int64_t averager_residual = 0;
	int64_t previous_frame_time = 0;
	int64_t frame_accumlator = 0;
	int64_t current_frame_time = 0;
	int64_t delta_time = 0;
	const int time_history_count = 4;
	int64_t averager_sum = 0;
	std::shared_ptr<GraphicsDevice> gameGraphicsDevice;
};
#endif