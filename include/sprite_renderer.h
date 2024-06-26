#ifndef SPRITE_RENDERER
#define SPRITE_RENDERER

#include <texture.h>
#include <graphics_device.h>
#include <vector2.h>
#include <colour.h>
#include <matrix.h>
#include <rectangle.h>
#include <sprite_mirror.h>
#include <vector>

class Shader;

class SpriteRenderer
{
public:
	SpriteRenderer(const SpriteRenderer& that) = default;
	SpriteRenderer(SpriteRenderer&& that) = default;
	SpriteRenderer& operator=(const SpriteRenderer& rhs) = default;
	SpriteRenderer& operator=(SpriteRenderer&& rhs) = default;
	SpriteRenderer(const GraphicsDevice& device);
	void Draw(Texture& texture, Vector2<float> position, Colour colour, SpriteMirror mirror);
	void Draw(Texture& texture, Vector2<float> position, Rectangle sourceRectangle, Colour colour, SpriteMirror mirror);
	void Draw(Texture& texture, Vector2<float> position, Rectangle sourceRectangle, Colour colour, SpriteMirror mirror, float rotation, Vector2<float> origin, float scale);
	void Draw(Texture& texture, Vector2<float> position, Rectangle sourceRectangle, Colour colour, SpriteMirror mirror, float rotation, Vector2<float> origin, Vector2<float> scale);
	void Draw(Texture& texture, Rectangle destinationRectangle, Colour colour, SpriteMirror mirror);
	void Draw(Texture& texture, Rectangle destionationRectangle, Rectangle sourceRectangle, Colour colour, SpriteMirror mirror);
	void Draw(Texture& texture, Rectangle destinationRectangle, Rectangle sourceRectangle, Colour colour, SpriteMirror mirror, float rotation, Vector2<float> origin);

private:
	void InitalizeRenderData(const GraphicsDevice& device);

	void PushVertexInformation(
		Texture& texture,
		float sourceX,
		float sourceY,
		float sourceWidth,
		float sourceHeight,
		float destinationX,
		float destinationY,
		float destinationWidth,
		float destionationHeight,
		Colour colour,
		float originX,
		float originY,
		float rotationSin,
		float rotationCos,
		SpriteMirror spriteMiror);

	Shader* shader;
	unsigned int quadVAO;
	unsigned int VBO;
};

#endif