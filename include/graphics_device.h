#ifndef GRAPHICS_DEVICE_H
#define GRAPHICS_DEVICE_H

#include <string>
#include "api.h"
#include <colour.h>

struct SDL_Window;

class KARAKURI_API GraphicsDevice
{
public:
	GraphicsDevice(const std::string& title, int width, int height, int scale);
	~GraphicsDevice();
	void Clear(Colour colour);
	void SwapBuffer();
	void EnableFullScreen(bool state);
	void EnableVSync(bool state);
	const int WindowWidth() const { return width; }
	const int WindowHeight() const { return height; }

private:
	const float color_range;
	const int scale;
	const int width;
	const int height;
	SDL_Window* window;
};
#endif