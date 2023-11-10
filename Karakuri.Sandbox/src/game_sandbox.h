#ifndef GAMESANDBOX_H
#define GAMESANDBOX_H

#include <game.h>
#include <texture.h>
#include <sprite_renderer.h>
#include <keyboard.h>
#include <glm/glm.hpp>
#include <gamepad.h>


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
	Keyboard* keyboard;
	Gamepad* gamepad;
	glm::vec2 position;
};

#endif