#ifndef SPRITE_RENDERER
#define SPRITE_RENDERER

#include "api.h"
#include <texture.h>
#include <graphics_device.h>
#include <vector2.h>
#include <colour.h>
#include <matrix.h>
#include <rectangle.h>

class Shader;

class KARAKURI_API SpriteRenderer
{
public:
	SpriteRenderer(const GraphicsDevice& device);
	void Draw(Texture& texture, Vector2<float> position, Rectangle draw_area, Vector2<float> size, float rotate, Colour colour, Matrix<float> camera);

private:
	void InitalizeRenderData(const GraphicsDevice& device);

	Shader* shader;
	unsigned int quadVAO;
};

#endif