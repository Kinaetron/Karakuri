#ifndef GRAPHICS_DEVICE_H
#define GRAPHICS_DEVICE_H

#include <string>
#include <colour.h>

struct SDL_Window;

class GraphicsDevice
{
public:
	GraphicsDevice() = default;
	GraphicsDevice(const GraphicsDevice& that) = default;
	GraphicsDevice(GraphicsDevice&& that) = default;
	GraphicsDevice& operator=(const GraphicsDevice& rhs) = default;
	GraphicsDevice& operator=(GraphicsDevice&& rhs) = default;
	GraphicsDevice(const std::string& title, int width, int height, int scale);
	void Clear(const Colour& colour);
	void SwapBuffer();
	void EnableFullScreen(bool state);
	void EnableVSync(bool state);
	const int WindowWidth() const { return width; }
	const int WindowHeight() const { return height; }
	void Destroy();

private:
	float color_range = 0;
	int scale = 0;
	int width = 0;
	int height = 0;
	SDL_Window* window = NULL;
};
#endif