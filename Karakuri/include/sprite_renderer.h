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
	void Draw(glm::vec2 position, Texture& texture);

private:
	int LoadTexture(Texture& texture);
	glm::mat4 projection;
};

#endif