#ifndef SPRITE_RENDERER
#define SPRITE_RENDERER

#include "api.h"
#include <texture.h>
#include <graphics_device.h>
#include <vector2.h>
#include <colour.h>
#include <matrix.h>
#include <rectangle.h>

class KARAKURI_API SpriteRenderer
{
public:
	SpriteRenderer(GraphicsDevice& device);
	void Draw(Texture& texture, Vector2<float> position, Rectangle draw_area, Vector2<float> size, float rotate, Colour color, Matrix<float> camera);

private:
	void InitalizeRenderData(GraphicsDevice& device);

	class Shader* shader;
	unsigned int quadVAO;
};

#endif