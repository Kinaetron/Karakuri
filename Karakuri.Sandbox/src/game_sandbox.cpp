#include "game_sandbox.h"
#include <iostream>
#include <buttons.h>
#include <keys.h>

GameSandbox::GameSandbox(std::string title, int width, int height)
	:Game(title, width, height)
{
	position = glm::vec2(0, 0);
	position2 = glm::vec2(500, 500);
	circleTexture = new Texture("resources/sprites/circle.png");
	rectangleTexture = new Texture("resources/sprites/rectangle.png");
	renderer = new SpriteRenderer(*graphicsDevice);
	keyboard = new Keyboard();

	circle = new Circle(50.0f, position);
	rectangle = new Rectangle(100.0f, 100.0f, position2);
	circleColor = glm::vec3(1, 1, 1);
}

void GameSandbox::Initialize()
{
	Game::Initialize();
	graphicsDevice->EnableVSync(false);
}

void GameSandbox::Update()
{
	Game::Update();
	keyboard->Update();

	if (keyboard->IsKeyDown(Keys::D)) {
		position.x += 0.002f;
	}

	if (keyboard->IsKeyDown(Keys::A)) {
		position.x -= 0.002f;
	}

	if (keyboard->IsKeyDown(Keys::W)) {
		position.y -= 0.002f;
	}

	if (keyboard->IsKeyDown(Keys::S)) {
		position.y += 0.002f;
	}

	circle->SetPosition(position);
	glm::vec2 result = circle->IntersectRectangle(*rectangle);

	if (result.x != 0 || result.y != 0) {
		circleColor = glm::vec3(1, 0, 0);
	}
	else {
		circleColor = glm::vec3(1, 1, 1);
	}

	if (keyboard->IsKeyDown(Keys::Escape)) {
		this->Quit();
	}
}

void GameSandbox::Draw()
{
	Game::Draw();
	graphicsDevice->Clear(0, 0, 0, 0);
	renderer->Draw(*circleTexture, circle->Centre(), glm::vec2(100, 100), 0, circleColor);
	renderer->Draw(*rectangleTexture, position2, glm::vec2(100, 100), 0, glm::vec3(1, 1, 1));
	graphicsDevice->SwapBuffer();
}