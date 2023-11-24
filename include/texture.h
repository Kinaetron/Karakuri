#ifndef TEXTURE_H
#define	TEXTURE_H

#include "api.h"
#include <string>

class KARAKURI_API Texture
{
public:
	Texture() = default;
	Texture(const Texture& that) = default;
	Texture(Texture&& that) = default;
	Texture& operator=(const Texture& rhs) = default;
	Texture& operator=(Texture&& rhs) = default;
	Texture(const std::string& filepath);
	const int Width() const { return width; }
	const int Height() const { return height; }
	const int ChannelType() const { return channelType; }
	void Bind();


private:
	int width = 0;
	int height = 0;
	int channelType = 0;
	unsigned int textureID = 0;
};

#endif