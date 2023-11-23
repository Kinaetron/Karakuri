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
	std::int64_t oldTime = 0;
	std::int64_t deltaTime = 0;
	double accumlator = 0.0;
	const std::int64_t TARGET_FRAME_RATE = 0;
	const double TARGET_FRAME_TIME = 0.0;
};
#endif