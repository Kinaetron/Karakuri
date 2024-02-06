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

	/*
	* Creates an object that represents a texture.
	* \param filepath, tells where the file that is being loaded up as a texture.
	*/
	Texture(const std::string& filepath);

	/*
	* Creates an object that represents a texture.
	* \param width, the width of the texture in pixels.
	* \param height, the height of the texture in pixels.
	* \param channel, the channel type of the texture 1 = Red, 3 = RGB, 4 = RGBA.
	*  \param pixels, an array of pixels which makes up the texture.
	*/
	Texture(int width, int height, int channel, unsigned char* pixels);


	/*
	* Gets the width of the texture.
	*/
	const int Width() const { return width; }

	/*
	* Gets the height of the texture.
	*/
	const int Height() const { return height; }

	/*
	* Gets the channel type of the texture.
	*/
	const int ChannelType() const { return channelType; }

	/*
	* Allows the texture to be used on the GPU
	*/
	void Bind();

	/*
	* Destroys the texture object.
	*/
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