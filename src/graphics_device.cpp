#include <graphics_device.h>
#include <vector3.h>

#include <spdlog/spdlog.h>
#include <iostream>
#include <SDL.h>
#include "glad.h"

GraphicsDevice::GraphicsDevice(const std::string& title, int width, int height, int scale):
	color_range(255.0f),
	width(width),
	height(height),
	scale(scale),
	window(nullptr),
	logger(nullptr)
{
	logger = spdlog::get("karakuri_logger");

	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		logger->error("SDL video initalization failed {}", SDL_GetError());
		return;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

 	 window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width * scale,
		height * scale,
		SDL_WINDOW_OPENGL
	);

	if (!window)
	{
		logger->error("Failed to create SDL window: {}", SDL_GetError());
		return;
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);

	if (!context)
	{
		logger->error("Failed to create SDL OpenGL context: {}", SDL_GetError());
		return;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		logger->error("Failed to initialize Glad {}", SDL_GetError());
		return;
	}

	if (!GLAD_GL_VERSION_4_0) 
	{
		logger->error("OpenGL 4.0 is not supported on this system", SDL_GetError());
		return;
	}

	GLuint framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
	{
		logger->error("Framebuffer creation failed!", SDL_GetError());
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, width * scale, height * scale);
}

void GraphicsDevice::Clear(const Colour& colour)
{
	Vector3<float> colour_vector = colour.ToVector3();

	glClearColor(colour_vector.X, colour_vector.Y, colour_vector.Z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}



void GraphicsDevice::SwapBuffer() {
	SDL_GL_SwapWindow(window);
}

void GraphicsDevice::EnableFullScreen(bool state) {
	SDL_SetWindowFullscreen(window, state);
}

void GraphicsDevice::EnableVSync(bool state) {
	SDL_GL_SetSwapInterval(state);
}

void GraphicsDevice::Destroy() 
{
	logger.reset();
	SDL_DestroyWindow(window);
}