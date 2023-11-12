#ifndef MOUSE_H
#define MOUSE_H

#include "api.h"
#include "buttons.h"
#include "../include/vector2.h"

#include <cstdint>

class KARAKURI_API Mouse
{
public:
	Mouse();
	void Update();
	const bool IsButtonUp(MouseButtons button);
	const bool IsButtonDown(MouseButtons button);
	const Vector2<int> Position() { return position; };

private:
	Vector2<int> position;
	uint32_t mouseState;
};
#endif