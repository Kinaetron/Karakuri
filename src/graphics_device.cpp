#include <graphics_device.h>
#include <vector3.h>

#include <iostream>
#include <SDL.h>
#include "glad.h"

GraphicsDevice::GraphicsDevice(std::string title, int width, int height, int scale):
	color_range(255.0f),
	width(width),
	height(height),
	scale(scale),
	window(NULL)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		std::cerr << "SDL video initalization failed" << SDL_GetError() << std::endl;
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
		std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
		return;
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);

	if (!context)
	{
		std::cerr << "Failed to create SDL OpenGL context: " << SDL_GetError() << std::endl;
		return;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cerr << "Failed to initialize Glad" << std::endl;
		return;
	}

	if (!GLAD_GL_VERSION_4_0) 
	{
		std::cerr << "OpenGL 4.0 is not supported on this system" << std::endl;
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
		std::cerr << "Framebuffer creation failed!" << std::endl;
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, width * scale, height * scale);
}

void GraphicsDevice::Clear(Colour colour)
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
