#ifndef SPRITE_RENDERER
#define SPRITE_RENDERER

#include "api.h"
#include "glm/glm.hpp"
#include "./texture.h"
#include "./graphics_device.h"

class KARAKURI_API SpriteRenderer
{
public:
	SpriteRenderer(GraphicsDevice& device);
	void Draw(Texture& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color);

private:
	void InitalizeRenderData(GraphicsDevice& device);

	class Shader* shader;
	unsigned int quadVAO;
};

#endif