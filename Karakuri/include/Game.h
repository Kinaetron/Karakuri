#ifndef GAME_H
#define GAME_H

#include <string>
#include <cstdint>
#include "graphics_device.h"
#include "api.h"

class KARAKURI_API Game
{
public:
	Game(std::string title, int width, int height);
	virtual void Initialize();
	virtual void Update();
	virtual void Draw();
	void Run();

	GraphicsDevice* graphicsDevice;

private:
	std::int64_t oldTime;
	std::int64_t deltaTime;
	double accumlator;
	const std::int64_t TARGET_FRAME_RATE;
	const double TARGET_FRAME_TIME;
};

#endif