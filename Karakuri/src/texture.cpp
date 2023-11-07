#include "stb_image.h"
#include <glad/glad.h>
#include "../include/texture.h"

Texture::Texture(const std::string& filepath)
	:width(0), height(0), channelType(0), textureID(0), data(NULL)
{
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(filepath.c_str(), &width, &height, &channelType, 0);
}