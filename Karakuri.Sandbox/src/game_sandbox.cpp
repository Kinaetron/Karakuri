#include "game_sandbox.h"
#include <iostream>
#include <keys.h>

GameSandbox::GameSandbox(std::string title, int width, int height)
	:Game(title, width, height)
{
	position = glm::vec2(200, 400);
	texture = new Texture("resources/sprites/luffy.jpg");
	renderer = new SpriteRenderer(*graphicsDevice);
	keyboard = new Keyboard();
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

	if (keyboard->IsKeyDown(Keys::Right))
	{
		position.x += 0.002f;
	}


	if (keyboard->IsKeyDown(Keys::Left))
	{
		position.x -= 0.002f;
	}
}

void GameSandbox::Draw()
{
	Game::Draw();
	graphicsDevice->Clear(0, 0, 0, 0);
	renderer->Draw(*texture, position, glm::vec2(540, 405), 0, glm::vec3(1, 1, 1));
	graphicsDevice->SwapBuffer();
}