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
	Game(const std::string& title, int width, int height, int scale);
	virtual void Initialize();
	virtual void Update();
	virtual void Draw();
	void Run();
	void Quit();
	const float MilliSecondsPerUpdate() const { return target_milliseconds_per_update; }

	GraphicsDevice graphicsDevice;

private:
	bool isRunning = true;
	void ProcessEvents();
	const float target_milliseconds_per_update;
	std::shared_ptr<spdlog::logger> logger;
};
#endif