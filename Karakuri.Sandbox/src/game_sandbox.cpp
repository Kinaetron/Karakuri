#include "game_sandbox.h"
#include <iostream>
#include <buttons.h>
#include <keys.h>

GameSandbox::GameSandbox(std::string title, int width, int height)
	:Game(title, width, height)
{
	position = glm::vec2(200, 400);
	texture = new Texture("resources/sprites/luffy.jpg");
	renderer = new SpriteRenderer(*graphicsDevice);
	keyboard = new Keyboard();
	gamepad = new Gamepad(0);
	mouse = new Mouse();
}

void GameSandbox::Initialize()
{
	Game::Initialize();
	graphicsDevice->EnableVSync(false);
}

void GameSandbox::Update()
{
	Game::Update();
	mouse->Update();
	gamepad->Udpate();
	keyboard->Update();

	if (gamepad->IsConnected()) 
	{
	}

	if (gamepad->RightThumbStick(0.1).x >= 0.5) {
		position.x += 0.002f;
	}

	if (gamepad->LeftTrigger() > 0.5) {
		position.x -= 0.002f;
	}

	if (keyboard->IsKeyDown(Keys::Right)) {
		position.x += 0.002f;
	}

	if (keyboard->IsKeyDown(Keys::Left)) {
		position.x -= 0.002f;
	}

	if (mouse->IsButtonDown(MouseButtons::MIDDLE))
	{
		std::cout << "Mouse X: " << mouse->Position().x << " Y: " << mouse->Position().y << std::endl;
	}
}

void GameSandbox::Draw()
{
	Game::Draw();
	graphicsDevice->Clear(0, 0, 0, 0);
	renderer->Draw(*texture, position, glm::vec2(540, 405), 0, glm::vec3(1, 1, 1));
	graphicsDevice->SwapBuffer();
}