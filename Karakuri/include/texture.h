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
	const unsigned char* Data() const { return data; }


private:
	int width;
	int height;
	int channelType;
	unsigned char* data;
};

#endif