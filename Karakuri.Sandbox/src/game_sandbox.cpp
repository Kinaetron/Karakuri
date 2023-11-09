#include "game_sandbox.h"
#include <graphics_device.h>

#include <iostream>
#include <texture.h>

GameSandbox::GameSandbox(std::string title, int width, int height)
	:Game(title, width, height)
{
	texture = new Texture("resources/sprites/luffy.jpg");
	renderer = new SpriteRenderer(*graphicsDevice);
}

void GameSandbox::Initialize()
{
	Game::Initialize();
}

void GameSandbox::Update()
{
	Game::Update();
}

void GameSandbox::Draw()
{
	graphicsDevice->Clear(0, 0, 0, 0);
	renderer->Draw(*texture, glm::vec2(200, 400), glm::vec2(540, 405), 0, glm::vec3(1, 1, 1));
	graphicsDevice->SwapBuffer();
	Game::Draw();
}