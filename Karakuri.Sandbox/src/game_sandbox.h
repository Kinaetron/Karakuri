#ifndef GAMESANDBOX_H
#define GAMESANDBOX_H

#include "game.h"
#include "graphics_device.h"

class GameSandbox : public Game
{
public:
	GameSandbox(std::string title, int width, int height);
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

#endif