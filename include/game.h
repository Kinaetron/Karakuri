#ifndef GAME_H
#define GAME_H

#include <string>
#include <cstdint>
#include "graphics_device.h"
#include <memory>

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

	GraphicsDevice graphicsDevice;

private:
	bool isRunning = true;
	void ProcessEvents();
};
#endif