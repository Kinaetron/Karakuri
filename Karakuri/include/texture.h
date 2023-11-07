#ifndef TEXTURE_H
#define	TEXTURE_H

#include <string>

class Texture
{
public:
	Texture(const std::string& filepath);
	const int Width() const { return width; }
	const int Height() const { return height; }
	const int ChannelType() const { return channelType; }
	const unsigned int TextureID() const { return textureID; }
	const unsigned char* Data() const { return data; }


private:
	int width;
	int height;
	int channelType;
	unsigned int textureID;
	unsigned char* data;
};

#endif