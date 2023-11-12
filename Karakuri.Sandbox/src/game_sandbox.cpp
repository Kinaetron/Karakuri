 #include "game_sandbox.h"
#include <iostream>
#include <buttons.h>
#include <keys.h>

GameSandbox::GameSandbox(std::string title, int width, int height)
	:Game(title, width, height)
{
	position = Vector2<float>::Zero();
	position2 = Vector2<float>(500.0f, 500.0f);
	circleTexture = new Texture("resources/sprites/circle.png");
	rectangleTexture = new Texture("resources/sprites/rectangle.png");
	renderer = new SpriteRenderer(*graphicsDevice);
	keyboard = new Keyboard();

	circle = new Circle(50.0f, position);
	rectangle = new Rectangle(100.0f, 100.0f, position2);
	circleColor = Vector3<float>(1.0f, 1.0f, 1.0f);
}

void GameSandbox::Initialize()
{
	Game::Initialize();
	graphicsDevice->EnableVSync(false);
}

void GameSandbox::Update()
{
	auto something = Vector2<float>::Zero();

	Game::Update();
	keyboard->Update();

	if (keyboard->IsKeyDown(Keys::D)) {
		position.X += 0.002f;
	}

	if (keyboard->IsKeyDown(Keys::A)) {
		position.X -= 0.002f;
	}

	if (keyboard->IsKeyDown(Keys::W)) {
		position.Y -= 0.002f;
	}

	if (keyboard->IsKeyDown(Keys::S)) {
		position.Y += 0.002f;
	}

	circle->SetPosition(position);
	Vector2<float> result = circle->IntersectRectangle(*rectangle);

	if (result.X != 0 || result.Y != 0) {
		circleColor = Vector3<float>(1.0f, 0.0f, 0.0f);
	}
	else {
		circleColor = Vector3<float>(1.0f, 1.0f, 1.0f);
	}

	if (keyboard->IsKeyDown(Keys::Escape)) {
		this->Quit();
	}
}

void GameSandbox::Draw()
{
	Game::Draw();
	graphicsDevice->Clear(0, 0, 0, 0);
	//renderer->Draw(*circleTexture, circle->Centre(), Vector2<float>(100.0f, 100.0f), 0, circleColor);
	renderer->Draw(*rectangleTexture, position2, Vector2<float>(100.0f, 100.0f), 0, Vector3<float>(1.0f, 1.0f, 1.0f));
	graphicsDevice->SwapBuffer();
}