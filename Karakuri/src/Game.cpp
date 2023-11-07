#include "../include/Game.h"
#include <SDL2/SDL.h>

Game::Game(std::string title, int width, int height)
	:oldTime(0), 
	 deltaTime(0), 
	 accumlator(0),
	 TARGET_FRAME_RATE(60)
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

		deltaTime = SDL_GetTicks64() - oldTime;
		oldTime = SDL_GetTicks64();
		accumlator += deltaTime;

		while (accumlator > 1.0 / TARGET_FRAME_RATE)
		{
			this->Update();
			accumlator -= 1.0 / TARGET_FRAME_RATE;
		}
		this->Draw();
	}
}
