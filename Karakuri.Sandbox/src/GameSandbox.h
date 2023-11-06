#ifndef GAMESANDBOX_H
#define GAMESANDBOX_H

#include "Game.h"
#include "GraphicsDevice.h"

class GameSandbox : public Game
{
public:
	GameSandbox(std::string title, int width, int height);
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

#endif