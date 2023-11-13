#ifndef GAMESANDBOX_H
#define GAMESANDBOX_H

#include <game.h>
#include <texture.h>
#include <sprite_renderer.h>
#include <keyboard.h>
#include <gamepad.h>
#include <mouse.h>
#include <rectangle.h>
#include <circle.h>
#include <vector2.h>
#include <vector3.h>
#include <gamepad.h>

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
	Gamepad* gamepad;

	Vector2<float> position;
	Vector2<float> position2;

	Circle* circle;
	Rectangle* rectangle;

	Vector3<float> circleColor;
};

#endif