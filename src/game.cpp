#include <game.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/sinks/basic_file_sink.h>

Game::Game(const std::string& title, int width, int height, int scale):
	 graphicsDevice(title, width, height, scale),
	 target_milliseconds_per_update(1000.0f / 60.0f),
	 logger(nullptr)
{
	auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/karakuri.txt", true);

	logger = std::make_shared<spdlog::logger>("karakuri_logger", spdlog::sinks_init_list{ console_sink, file_sink });
	spdlog::register_logger(logger);

	file_sink.reset();
	console_sink.reset();

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		logger->error("SDL sound initialization failed: {}", SDL_GetError());
		return;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		logger->error("SDL open audio initalization failed: {}", SDL_GetError());
		return;
	}

	if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) 
	{
		logger->error("SDL game pad initalization failed: {}", SDL_GetError());
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

void Game::ProcessEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
	}
}

void Game::Run()
{
	this->Initialize();

	std::int64_t previous = 0;
	std::int64_t lag = 0;

	while (isRunning)
	{
		this->ProcessEvents();

		std::int64_t current = SDL_GetTicks64();
		std::int64_t elapsed = current - previous;
		previous = current;
		lag += elapsed;

		while (lag >= target_milliseconds_per_update)
		{
			this->Update();
			lag -= static_cast<int64_t>(target_milliseconds_per_update);
		}

		this->Draw();
	}
}

void Game::Quit() 
{
	logger.reset();;
	graphicsDevice.Destroy();
	SDL_Quit();
}
