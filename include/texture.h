#ifndef TEXTURE_H
#define	TEXTURE_H

#include <array>
#include <string>
#include <memory>

namespace spdlog {
	class logger;
}

class Texture
{
public:
	Texture(const Texture& that) = default;
	Texture(Texture&& that) = default;
	Texture& operator=(const Texture& rhs) = default;
	Texture(const std::string& filepath);
	Texture(int width, int height, int channel, unsigned char* pixels);
	const int Width() const { return width; }
	const int Height() const { return height; }
	const int ChannelType() const { return channelType; }
	void Bind();
	void Destroy();


private:
	int width;
	int height;
	int channelType;
	unsigned int textureID;
	void LoadData(unsigned char* pixels);
	std::shared_ptr<spdlog::logger> logger;
};

#endif