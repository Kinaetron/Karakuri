#ifndef GAME_H
#define GAME_H

#include <string>
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
};

#endif