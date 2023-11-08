#ifndef GAMESANDBOX_H
#define GAMESANDBOX_H

#include <game.h>
#include <texture.h>
#include <sprite_renderer.h>
#include <graphics_device.h>

class GameSandbox : public Game
{
public:
	GameSandbox(std::string title, int width, int height);
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	Texture* texture;
	SpriteRenderer* renderer;

};

#endif