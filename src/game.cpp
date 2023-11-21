#include <game.h>
#include <SDL.h>
#include <iostream>
#include <SDL_mixer.h>

#include "../include/gamepad.h"

Game::Game(const std::string& title, int width, int height, int scale)
	:oldTime(0), 
	 deltaTime(0), 
	 accumlator(0),
	 TARGET_FRAME_RATE(60),
	 TARGET_FRAME_TIME(1.0 / TARGET_FRAME_RATE)
{
	graphicsDevice = std::make_unique<GraphicsDevice>(title, width, height, scale);

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		std::cerr << "SDL sound initialization failed" << SDL_GetError() << std::endl;
		return;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "SDL open audio initalization failed" << SDL_GetError() << std::endl;
		return;
	}

	if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
		std::cerr << "SDL game pad initalization failed" << SDL_GetError() << std::endl;
		return;
	}
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

		while (accumlator > TARGET_FRAME_TIME)
		{
			this->Update();
			accumlator -= TARGET_FRAME_TIME;
		}
		this->Draw();
	}
}

void Game::Quit() {
	SDL_Quit();
}
