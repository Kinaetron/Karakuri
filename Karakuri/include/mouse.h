#ifndef MOUSE_H
#define MOUSE_H

#include "api.h"
#include "glm/glm.hpp"
#include "buttons.h"

#include <cstdint>

class KARAKURI_API Mouse
{
public:
	Mouse();
	void Update();
	const bool IsButtonUp(MouseButtons button);
	const bool IsButtonDown(MouseButtons button);
	const glm::ivec2 Position() { return position; };

private:
	glm::ivec2 position;
	uint32_t mouseState;
};
#endif