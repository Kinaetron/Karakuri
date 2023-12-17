#ifndef GRAPHICS_DEVICE_H
#define GRAPHICS_DEVICE_H

#include <memory>
#include <string>
#include <colour.h>

namespace spdlog {
	class logger;
}

struct SDL_Window;

class GraphicsDevice
{
public:
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
	float color_range;
	int scale;
	int width;
	int height;
	SDL_Window* window;
	std::shared_ptr<spdlog::logger> logger;
};
#endif