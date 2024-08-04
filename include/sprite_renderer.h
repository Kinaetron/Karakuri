#ifndef SPRITE_RENDERER
#define SPRITE_RENDERER

#include <shader.h>
#include <texture.h>
#include <graphics_device.h>
#include <vector2.h>
#include <colour.h>
#include <matrix.h>
#include <rectangle.h>
#include <sprite_mirror.h>
#include <vector>

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

	std::string vertexShader = R"(
		#version 400 core

		layout (location = 0) in vec2 vertex;
		layout (location = 1) in vec2 texCoord;
	    layout (location = 2) in vec3 colour;

		out vec2 TexCoord;
		out vec3 TexColour;

		uniform mat4 matrix;

		void main()
		{
			TexCoord = texCoord;
			TexColour = colour;
			
			gl_Position = matrix * vec4(vertex, 0.0, 1.0);
		}
	)";

	std::string fragmentShader = R"(
		#version 400 core

		in vec2 TexCoord;
		in vec3 TexColour;

		out vec4 colour;

		uniform sampler2D image;

		void main()
		{
			colour = texture(image, TexCoord) * vec4(TexColour, 1.0);
			if (colour.a < 0.5) discard;
		}
	)";

	Shader shader;
	unsigned int quadVAO;
	unsigned int VBO;
};

#endif