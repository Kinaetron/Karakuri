#ifndef GRAPHICS_DEVICE_H
#define GRAPHICS_DEVICE_H

#include <string>
#include "API.h"

class KARAKURI_API GraphicsDevice
{
public:
	GraphicsDevice(std::string title, int width, int height);
	void Clear(unsigned short red, unsigned short green, unsigned short blue, unsigned short alpha);
	void SwapBuffer();
	void FullScreen(bool state);

private:
	const float color_range;
};
#endif