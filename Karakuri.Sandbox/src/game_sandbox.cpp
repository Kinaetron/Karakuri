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
	graphicsDevice->Clear(100, 100, 100, 0);
	
	renderer->Draw(glm::vec2(100, 100), *texture);

	graphicsDevice->SwapBuffer();
	Game::Draw();
}