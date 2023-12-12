#ifndef TEXTURE_H
#define	TEXTURE_H

#include <array>
#include <string>

class Texture
{
public:
	Texture() = default;
	Texture(const Texture& that) = default;
	Texture(Texture&& that) = default;
	Texture& operator=(const Texture& rhs) = default;
	Texture(const std::string& filepath);
	Texture(int width, int height, int channel, unsigned char* pixels);
	const int Width() const { return width; }
	const int Height() const { return height; }
	const int ChannelType() const { return channelType; }
	void Bind();


private:
	int width = 0;
	int height = 0;
	int channelType = 0;
	unsigned int textureID = 0;
	void LoadData(unsigned char* pixels);
};

#endif