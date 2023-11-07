#ifndef GAME_H
#define GAME_H

#include <string>
#include <cstdint>
#include "GraphicsDevice.h"
#include "API.h"

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
	std::uint64_t oldTime;
	std::uint64_t deltaTime;
	std::uint64_t accumlator;
	const std::uint64_t TARGET_FRAME_RATE;
};

#endif