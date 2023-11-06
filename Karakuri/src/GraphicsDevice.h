#ifndef GRAPHICS_DEVICE_H
#define GRAPHICS_DEVICE_H

#include <string>
#include "API.h"

class KARAKURI_API GraphicsDevice
{
public:
	GraphicsDevice(std::string title, int width, int height);
	void Clear();
	void SwapBuffer();
};
#endif