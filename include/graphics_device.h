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

	/*
	* Deals with the creation of the window and graphics state of the game.
	* \param title sets the name of the window.
	* \param width sets the width of the window.
	* \param height sets the height of the window.
	* \param scale sets the scale of the window. It scales up the window size by that scale will keeping the resolution the same.
	*/
	GraphicsDevice(const std::string& title, int width, int height, int scale);

	/*
	* Clears the colour buffer.
	* \param colour, sets the colour the colour buffer will be cleared to.
	*/
	void Clear(const Colour& colour);

	/*
	* Swaps the buffer.
	*/
	void SwapBuffer();

	/*
	* Sets the screen to be fullscreen.
	*/
	void EnableFullScreen(bool state);

	/*
	* Sets the vsync.
	*/
	void EnableVSync(bool state);

	/*
	* Gets the width of the window.
	*/
	const int WindowWidth() const { return width; }

	/*
	* Gets the width of the window.
	*/
	const int WindowHeight() const { return height; }

	/*
	* Destroys the graphics objects
	*/
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