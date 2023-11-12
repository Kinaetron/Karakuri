#ifndef SPRITE_RENDERER
#define SPRITE_RENDERER

#include "api.h"
#include "./texture.h"
#include "./graphics_device.h"
#include "../include/vector2.h"
#include "../include/vector3.h"

class KARAKURI_API SpriteRenderer
{
public:
	SpriteRenderer(GraphicsDevice& device);
	void Draw(Texture& texture, Vector2<float> position, Vector2<float> size, float rotate, Vector3<float> color);

private:
	void InitalizeRenderData(GraphicsDevice& device);

	class Shader* shader;
	unsigned int quadVAO;
};

#endif