#include "Game.h"
#include <SDL2/SDL.h>

Game::Game(std::string title, int width, int height)
{
	graphicsDevice = new GraphicsDevice(title, width, height);
}

void Game::Initialize()
{
}

void Game::Update()
{
}

void Game::Draw()
{
}

void Game::Run()
{
	this->Initialize();

	bool isRunning = true;
	while (isRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
		}

		this->Update();
		this->Draw();
	}
}
