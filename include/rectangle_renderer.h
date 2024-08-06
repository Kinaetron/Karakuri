#ifndef RECTANGLE_RENDERER_H
#define RECTANGLE_RENDERER_H

#include <rectangle.h>
#include <graphics_device.h>

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
};
#endif // !RECTANGLE_RENDERER_H
