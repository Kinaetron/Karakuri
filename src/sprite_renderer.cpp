#include <iostream>
#include <string>
#include <cmath>
#include <limits>
#include <algorithm>

#include "glad.h"
#include <math_utility.h>
#include <sprite_renderer.h>
#include <vector2.h>
#include "shader.h"

SpriteRenderer::SpriteRenderer(const GraphicsDevice& device)
{
	InitalizeRenderData(device);
}

void SpriteRenderer::InitalizeRenderData(const GraphicsDevice& device)
{
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

	Matrix<float> projection =  Matrix<float>::OrthographicProjection(0, static_cast<float>(device.WindowWidth()),
		static_cast<float>(device.WindowHeight()), 0.0f, -1.0f, 1.0f);

	shader = new Shader(vertexShader, fragmentShader);

	shader->Use();
	shader->SetInteger("image", 0);
	shader->SetMatrix4("matrix", projection);

	float vertices[] =
	{
		// positions // texture coords // colours 
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // top right
		1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom right
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
		0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // top left 
	};

	unsigned int indices[] =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	unsigned int EBO;

	glGenVertexArrays(1, &this->quadVAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(this->quadVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(4 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteRenderer::Draw(Texture& texture, Vector2<float> position, Colour colour, SpriteMirror mirror)
{
	PushVertexInformation( 
		texture,
		0.0f,
		0.0f,
		1.0f,
		1.0f,
		position.X,
		position.Y,
		static_cast<float>(texture.Width()),
		static_cast<float>(texture.Height()),
		colour,
		0.0f,
		0.0f,
		0.0f,
		1.0f,
		mirror);
}

void SpriteRenderer::Draw(Texture& texture, Vector2<float> position, Rectangle sourceRectangle, Colour colour, SpriteMirror mirror)
{
	float sourceX = sourceRectangle.Position().X / static_cast<float>(texture.Width());
	float sourceY = sourceRectangle.Position().Y / static_cast<float>(texture.Height());
	float sourceWidth = sourceRectangle.Width() / static_cast<float>(texture.Width());
	float sourceHeight = sourceRectangle.Height() / static_cast<float>(texture.Height());
	float destinationWidth = sourceRectangle.Width();
	float destinationHeight = sourceRectangle.Height();

	PushVertexInformation(
		texture,
		sourceX,
		sourceY,
		sourceWidth,
		sourceHeight,
		position.X,
		position.Y,
		destinationWidth,
		destinationHeight,
		colour,
		0.0f,
		0.0f,
		0.0f,
		1.0f,
		mirror
	);
}

void SpriteRenderer::Draw(Texture& texture, Vector2<float> position, Rectangle sourceRectangle, Colour colour, SpriteMirror mirror, float rotation, Vector2<float> origin, float scale)
{
	float destinationWidth = scale;
	float destinationHeight = scale;

	float sourceX = sourceRectangle.Position().X / static_cast<float>(texture.Width());
	float sourceY = sourceRectangle.Position().Y / static_cast<float>(texture.Height());

	float sourceWidth = MathUtility<float>::Sign(sourceRectangle.Width()) * 
		std::max(std::abs(sourceRectangle.Width()), std::numeric_limits<float>::epsilon()) 
		/ static_cast<float>(texture.Width());

	float sourceHeight = MathUtility<float>::Sign(sourceRectangle.Height()) *
		std::max(std::abs(sourceRectangle.Height()), std::numeric_limits<float>::epsilon())
		/ static_cast<float>(texture.Height());

	destinationWidth *= sourceRectangle.Width();
	destinationHeight *= sourceRectangle.Height();

	PushVertexInformation(
		texture,
		sourceX,
		sourceY,
		sourceWidth,
		sourceHeight,
		position.X,
		position.Y,
		destinationWidth,
		destinationHeight,
		colour,
		origin.X / sourceWidth / static_cast<float>(texture.Width()),
		origin.Y / sourceHeight / static_cast<float>(texture.Height()),
		static_cast<float>(std::sin(rotation)),
		static_cast<float>(std::cos(rotation)),
		mirror
	);
}

void SpriteRenderer::Draw(Texture& texture, Vector2<float> position, Rectangle sourceRectangle, Colour colour, SpriteMirror mirror, float rotation, Vector2<float> origin, Vector2<float> scale)
{
	float sourceX = sourceRectangle.Position().X / static_cast<float>(texture.Width());
	float sourceY = sourceRectangle.Position().Y / static_cast<float>(texture.Height());

	float sourceWidth = MathUtility<float>::Sign(sourceRectangle.Width()) *
		std::max(std::abs(sourceRectangle.Width()), std::numeric_limits<float>::epsilon())
		/ static_cast<float>(texture.Width());

	float sourceHeight = MathUtility<float>::Sign(sourceRectangle.Height()) *
		std::max(std::abs(sourceRectangle.Height()), std::numeric_limits<float>::epsilon())
		/ static_cast<float>(texture.Height());

	scale.X *= sourceRectangle.Width();
	scale.Y *= sourceRectangle.Height();

	PushVertexInformation(
		texture,
		sourceX,
		sourceY,
		sourceWidth,
		sourceHeight,
		position.X,
		position.Y,
		scale.X,
		scale.Y,
		colour,
		origin.X / sourceWidth / static_cast<float>(texture.Width()),
		origin.Y / sourceHeight / static_cast<float>(texture.Height()),
		std::sin(rotation),
		std::cos(rotation),
		mirror
	);
}

void SpriteRenderer::Draw(Texture& texture, Rectangle destinationRectangle, Colour colour, SpriteMirror mirror)
{
	PushVertexInformation
	(texture,
		0.0f,
		0.0f,
		1.0f,
		1.0f,
		destinationRectangle.Position().X,
		destinationRectangle.Position().Y,
		destinationRectangle.Width(),
		destinationRectangle.Height(),
		colour,
		0.0f,
		0.0f,
		0.0f,
		1.0f,
		mirror
	);
}

void SpriteRenderer::Draw(Texture& texture, Rectangle destionationRectangle, Rectangle sourceRectangle, Colour colour, SpriteMirror mirror)
{
	float sourceX = sourceRectangle.Position().X / static_cast<float>(texture.Width());
	float sourceY = sourceRectangle.Position().Y / static_cast<float>(texture.Height());
	float sourceWidth = sourceRectangle.Width() / static_cast<float>(texture.Width());
	float sourceHeight = sourceRectangle.Height() / static_cast<float>(texture.Height());

	PushVertexInformation
	(texture,
		sourceX,
		sourceY,
		sourceWidth,
		sourceHeight,
		destionationRectangle.Position().X,
		destionationRectangle.Position().Y,
		destionationRectangle.Width(),
		destionationRectangle.Height(),
		colour,
		0.0f,
		0.0f,
		0.0f,
		1.0f,
		mirror);
}

void SpriteRenderer::Draw(Texture& texture, Rectangle destinationRectangle, Rectangle sourceRectangle, Colour colour, SpriteMirror mirror, float rotation, Vector2<float> origin)
{
	float sourceX = sourceRectangle.Position().X / static_cast<float>(texture.Width());
	float sourceY = sourceRectangle.Position().Y / static_cast<float>(texture.Height());

	float sourceWidth = MathUtility<float>::Sign(sourceRectangle.Width()) *
		std::max(std::abs(sourceRectangle.Width()), std::numeric_limits<float>::epsilon())
		/ static_cast<float>(texture.Width());

	float sourceHeight = MathUtility<float>::Sign(sourceRectangle.Height()) *
		std::max(std::abs(sourceRectangle.Height()), std::numeric_limits<float>::epsilon())
		/ static_cast<float>(texture.Height());

	PushVertexInformation(
		texture,
		sourceX,
		sourceY,
		sourceWidth,
		sourceHeight,
		destinationRectangle.Position().X,
		destinationRectangle.Position().Y,
		destinationRectangle.Width(),
		destinationRectangle.Height(),
		colour,
		origin.X / sourceWidth / static_cast<float>(texture.Width()),
		origin.Y / sourceHeight / static_cast<float>(texture.Height()),
		std::sin(rotation),
		std::cos(rotation),
		mirror
	);
}

void SpriteRenderer::PushVertexInformation(
	Texture& texture, 
	float sourceX, 
	float sourceY, 
	float sourceWidth, 
	float sourceHeight, 
	float destinationX, 
	float destinationY, 
	float destinationWidth, 
	float destinationHeight,
	Colour colour,
	float originX,
	float originY,
	float rotationSin, 
	float rotationCos,
	SpriteMirror spriteMirror)
{
	Vector3<float> colourVector = colour.ToVector3();

	float cornerX = (1.0f - originX) * destinationWidth;
	float cornerY = (1.0f - originY) * destinationHeight;

	Vector2<float> position0 = Vector2<float>(
		(-rotationSin * cornerY) + (rotationCos * cornerX) + destinationX,
		(rotationCos * cornerY) + (rotationSin * cornerX) + destinationY);

	cornerX = (1.0f - originX) * destinationWidth;
	cornerY = -originY * destinationHeight;

	Vector2<float> position1 = Vector2<float>(
		(-rotationSin * cornerY) + (rotationCos * cornerX) + destinationX,
		(rotationCos * cornerY) + (rotationSin * cornerX) + destinationY);

	cornerX = -originX * destinationWidth;
	cornerY = -originY * destinationHeight;

	Vector2<float> position2 = Vector2<float>(
		(-rotationSin * cornerY) + (rotationCos * cornerX) + destinationX,
		(rotationCos * cornerY) + (rotationSin * cornerX) + destinationY);

	cornerX = -originX * destinationWidth;
	cornerY = (1.0f - originY) * destinationHeight;

	Vector2<float> position3 = Vector2<float>(
		(-rotationSin * cornerY) + (rotationCos * cornerX) + destinationX,
		(rotationCos * cornerY) + (rotationSin * cornerX) + destinationY);


	uint32_t cornerX0 = 0;
	uint32_t cornerX1 = 0;
	uint32_t cornerX2 = 0;
	uint32_t cornerX3 = 0;

	uint32_t cornerY0 = 0;
	uint32_t cornerY1 = 0;
	uint32_t cornerY2 = 0;
	uint32_t cornerY3 = 0;

	if (spriteMirror == SpriteMirror::None)
	{
		cornerX0 = 1;
		cornerY0 = 1;
		cornerX1 = 1;
		cornerY3 = 1;
	}
	else if (spriteMirror == SpriteMirror::Horizontally)
	{
		cornerY0 = 1;
		cornerX2 = 1;
		cornerX3 = 1;
		cornerY3 = 1;
	}
	else if (spriteMirror == SpriteMirror::Vertically)
	{
		cornerX0 = 1;
		cornerX1 = 1;
		cornerY1 = 1;
		cornerY2 = 1;
	}
	else if (spriteMirror == SpriteMirror::Both)
	{
		cornerY1 = 1;
		cornerX2 = 1;
		cornerY2 = 1;
		cornerX3 = 1;
	}


	Vector2<float> texCoords0 = Vector2<float>((cornerX0 * sourceWidth) + sourceX, 
											   (cornerY0 * sourceHeight) + sourceY);

	Vector2<float> texCoords1 = Vector2<float>((cornerX1 * sourceWidth) + sourceX,
											   (cornerY1 * sourceHeight) + sourceY);

	Vector2<float> texCoords2 = Vector2<float>((cornerX2 * sourceWidth) + sourceX, 
											   (cornerY2 * sourceHeight) + sourceY);

	Vector2<float> texCoords3 = Vector2<float>((cornerX3 * sourceWidth) + sourceX, 
											   (cornerY3 * sourceHeight) + sourceY);

	float vertices[] =
	{
		// positions			  // texture coords			  // colour 
		position0.X, position0.Y, texCoords0.X, texCoords0.Y, colourVector.X,  colourVector.Y, colourVector.Z,	// top right
		position1.X, position1.Y, texCoords1.X, texCoords1.Y, colourVector.X,  colourVector.Y, colourVector.Z,	// bottom right
		position2.X, position2.Y, texCoords2.X, texCoords2.Y, colourVector.X,  colourVector.Y, colourVector.Z,	// bottom left
		position3.X, position3.Y, texCoords3.X, texCoords3.Y, colourVector.X,  colourVector.Y, colourVector.Z,	// top left 
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader->Use();

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(quadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}