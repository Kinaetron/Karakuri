#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"
#include "texture.h"
#include "graphics_device.h"
#include "vector2.h"
#include "colour.h"
#include "matrix.h"
#include "rectangle.h"
#include "sprite_mirror.h"
#include <memory>
#include <string>

namespace spdlog {
	class logger;
}

class Renderer
{
public:
	Renderer(const Renderer& that) = default;
	Renderer(Renderer&& that) = default;
	Renderer& operator=(const Renderer& rhs) = default;
	Renderer& operator=(Renderer&& rhs) = default;
	Renderer(const std::shared_ptr<const GraphicsDevice> graphicsDevice);
	void State(Matrix<float> matrix);
	void DrawSprite(Texture& texture, Vector2<float> position, Colour colour, SpriteMirror mirror);
	void DrawSprite(Texture& texture, Rectangle destinationRectangle, Colour colour, SpriteMirror mirror);
	void DrawSprite(Texture& texture, Vector2<float> position, Rectangle sourceRectangle, Colour colour, SpriteMirror mirror);
	void DrawSprite(Texture& texture, Rectangle destionationRectangle, Rectangle sourceRectangle, Colour colour, SpriteMirror mirror);
	void DrawSprite(Texture& texture, Rectangle destinationRectangle, Rectangle sourceRectangle, Colour colour, SpriteMirror mirror, float rotation, Vector2<float> origin);
	void DrawSprite(Texture& texture, Vector2<float> position, Rectangle sourceRectangle, Colour colour, SpriteMirror mirror, float rotation, Vector2<float> origin, float scale);
	void DrawSprite(Texture& texture, Vector2<float> position, Rectangle sourceRectangle, Colour colour, SpriteMirror mirror, float rotation, Vector2<float> origin, Vector2<float> scale);
	void DrawRectangle(Rectangle destinationRectangle, Colour colour, unsigned short transparancy);

private:
	void PushVertexInformation(
		Texture* texture,
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
		SpriteMirror spriteMirror,
		unsigned short transparancy);

private:
	std::string vertexShader = R"(
		#version 400 core
		
		layout (location = 0) in vec2 vertex;
		layout (location = 1) in vec2 texCoord;
		layout (location = 2) in vec4 colour;
		
		out vec2 TexCoord;
		out vec4 Colour;

		uniform mat4 matrix;
		
		void main()
		{
			TexCoord = texCoord;
			Colour = colour;
			
			gl_Position = matrix * vec4(vertex, 0.0, 1.0);
		}
	)";

	std::string fragmentShader = R"(
		#version 400 core
		
		in vec2 TexCoord;
		in vec4 Colour;
		
		out vec4 colour;

		uniform sampler2D image;

		void main()
		{
			if(textureSize(image, 0).x > 1) 
			{
				colour = texture(image, TexCoord) * Colour;
				if (colour.a < 0.5) discard;
			}
			else {
				colour = Colour;
			}
		}
	)";

	Matrix<float> stateMatrix;
	Matrix<float> projectionMatrix;
	Shader shader;
	unsigned int quadVAO;
	unsigned int VBO;
	std::shared_ptr<spdlog::logger> logger;
};
#endif // !RENDERER_H