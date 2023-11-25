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
	SpriteRenderer() = default;
	SpriteRenderer(const SpriteRenderer& that) = default;
	SpriteRenderer(SpriteRenderer&& that) = default;
	SpriteRenderer& operator=(const SpriteRenderer& rhs) = default;
	SpriteRenderer& operator=(SpriteRenderer&& rhs) = default;
	SpriteRenderer(const GraphicsDevice& device);
	void Draw(Texture& texture, Vector2<float> position, Rectangle sourceRectangle, Colour colour, float rotation, Vector2<float> origin, Vector2<float> scale);

private:
	void InitalizeRenderData(const GraphicsDevice& device);

	Shader* shader = nullptr;
	unsigned int quadVAO = 0;
};

#endif