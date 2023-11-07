#include "GameSandbox.h"
#include "GraphicsDevice.h"
#include <iostream>

GameSandbox::GameSandbox(std::string title, int width, int height)
	:Game(title, width, height)
{
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
	graphicsDevice->SwapBuffer();
	Game::Draw();
}