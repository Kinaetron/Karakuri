#ifndef GAME_H
#define GAME_H

#include <string>
#include <cstdint>
#include "graphics_device.h"
#include "api.h"
#include <memory>

class KARAKURI_API Game
{
public:
	Game() = default;
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