#include "stb_image.h"
#include "glad.h"
#include <texture.h>

#include <iostream>

Texture::Texture(const std::string& filepath)
	:width(0), height(0), channelType(0), textureID(0)
{
	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channelType, 0);

	if (!data) {
		std::cerr << "Texture failed to load at path: " << filepath << std::endl;
	}

	LoadData(data);

	stbi_image_free(data);
}

void Texture::LoadData(unsigned char* pixels)
{
	glGenTextures(1, &textureID);

	GLenum format;

	switch (this->ChannelType())
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
		return;
	}

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, this->Width(), this->Height(), 0, format, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(int width, int height, int channel, unsigned char* pixels)
	:width(width), height(height), channelType(channel), textureID(0)
{
	LoadData(pixels);
}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}
