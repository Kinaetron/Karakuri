#include <iostream>
#include <glad/glad.h>
#include "../include/sprite_renderer.h"
#include "../include/glm/ext/matrix_clip_space.hpp"

SpriteRenderer::SpriteRenderer(GraphicsDevice& device)
{
	projection = glm::ortho(0.0f, static_cast<float>(device.WindowWidth()),
		static_cast<float>(device.WindowHeight()), 0.0f, -1.0f, 1.0f);
}

void SpriteRenderer::Draw(glm::vec2 position, Texture& texture)
{
	unsigned int texureID = LoadTexture(texture);
}

int SpriteRenderer::LoadTexture(Texture& texture)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	
	GLenum format; 

	switch (texture.ChannelType())
	{
		case 1:
			format = GL_RED;
			break;

		case 3:
			format = GL_RGB;
			break;

		case 4:
			format = GL_RGBA;
			break;

		default:
			std::cerr << "Channel type isn't supported" << std::endl;
			return - 1;
	}

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, texture.Width(), texture.Height(), 0, format, GL_UNSIGNED_BYTE, texture.Data());
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return textureID;
}