#ifndef RECTANGLE_RENDERER_H
#define RECTANGLE_RENDERER_H

#include <memory>
#include <rectangle.h>
#include <graphics_device.h>

namespace spdlog {
	class logger;
}

class Shader;

class RectangleRenderer
{
public:
	RectangleRenderer(const RectangleRenderer& that) = default;
	RectangleRenderer(RectangleRenderer&& that) = default;
	RectangleRenderer& operator=(const RectangleRenderer& rhs) = default;
	RectangleRenderer& operator=(RectangleRenderer&& rhs) = default;
	RectangleRenderer(const std::shared_ptr<const GraphicsDevice> graphicsDevice);

	void Draw(Rectangle destinationRectangle, Colour colour, unsigned short transparancy);

private:
	Shader* shader;
	unsigned int quadVAO;
	unsigned int VBO;
	std::shared_ptr<spdlog::logger> logger;
};
#endif // !RECTANGLE_RENDERER_H
