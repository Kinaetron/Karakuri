#ifndef GAMESANDBOX_H
#define GAMESANDBOX_H

#include <game.h>
#include <texture.h>
#include <sprite_renderer.h>
#include <keyboard.h>
#include <glm/glm.hpp>
#include <gamepad.h>
#include <mouse.h>
#include <rectangle.h>
#include <circle.h>


class GameSandbox : public Game
{
public:
	GameSandbox(std::string title, int width, int height);
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	Texture* circleTexture;
	Texture* rectangleTexture;
	SpriteRenderer* renderer;
	Keyboard* keyboard;
	glm::vec2 position;
	glm::vec2 position2;

	Circle* circle;
	Rectangle* rectangle;

	glm::vec3 circleColor;
};

#endif