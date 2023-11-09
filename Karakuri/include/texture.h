#ifndef TEXTURE_H
#define	TEXTURE_H

#include "api.h"
#include <string>

class KARAKURI_API Texture
{
public:
	Texture(const std::string& filepath);
	const int Width() const { return width; }
	const int Height() const { return height; }
	const int ChannelType() const { return channelType; }
	void Bind();


private:
	int width;
	int height;
	int channelType;
	unsigned char* data;
	unsigned int textureID;
};

#endif