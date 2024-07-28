#include <game.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include <spdlog/spdlog.h>

Game::Game(const std::string& title, int width, int height, int scale) :
	graphicsDevice(title, width, height, scale),
	logger(nullptr)
{
	logger = spdlog::get("engine_logger");

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

	clocks_per_second = SDL_GetPerformanceFrequency();
	fixed_deltatime = 1.0 / update_rate;
	desired_frametime = clocks_per_second / update_rate;

	vsync_maxerror = clocks_per_second * .0002;

	int displayIndex = SDL_GetWindowDisplayIndex(graphicsDevice.window);

	SDL_DisplayMode current_display_mode;
	if (SDL_GetCurrentDisplayMode(displayIndex, &current_display_mode) == 0) {
		display_framerate = current_display_mode.refresh_rate;
	}

	snap_hz = display_framerate;
	if (snap_hz <= 0) snap_hz = 60;

	for (int i = 0; i < 8; i++) {
		snap_frequencies[i] = (clocks_per_second / snap_hz) * (i + 1);
	}

	for (int i = 0; i < time_history_count; i++) {
		time_averager[i] = desired_frametime;
	}

	previous_frame_time = SDL_GetPerformanceCounter();

	std::string platform = reinterpret_cast<const char*>(SDL_GetPlatform());

	logger->info("the platform is: {}", platform);
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

void Game::Pause(float timeToStop) {
	SDL_Delay(timeToStop);
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

	// This game reference is being heavily reference from this  example 
	// https://github.com/TylerGlaiel/FrameTimingControl/blob/master/frame_timer.cpp
	while (isRunning)
	{
		current_frame_time = SDL_GetPerformanceCounter();
		delta_time = current_frame_time - previous_frame_time;
		previous_frame_time = current_frame_time;

		if (delta_time > desired_frametime * 8) {
			delta_time = desired_frametime;
		}

		if (delta_time < 0) {
			delta_time = 0;
		}

		for (int64_t snap : snap_frequencies)
		{
			if (std::abs(delta_time - snap) < vsync_maxerror)
			{
				delta_time = snap;
				break;
			}
		}

		for (int i = 0; i < time_history_count - 1; i++) {
			time_averager[i] = time_averager[i + 1];
		}

		time_averager[time_history_count - 1] = delta_time;

		averager_sum = 0;

		for (int i = 0; i < time_history_count; i++) {
			averager_sum += time_averager[i];
		}

		delta_time = averager_sum / time_history_count;

		averager_residual += averager_sum % time_history_count;
		delta_time += averager_residual / time_history_count;
		averager_residual %= time_history_count;

		frame_accumlator += delta_time;

		if (frame_accumlator > desired_frametime * 8) {
			resync = true;
		}

		if (resync)
		{
			frame_accumlator = 0;
			delta_time = desired_frametime;
			resync = false;
		}

		this->ProcessEvents();

		while (frame_accumlator >= desired_frametime)
		{
			this->Update();
			frame_accumlator -= desired_frametime;
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
