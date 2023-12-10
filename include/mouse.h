#ifndef MOUSE_H
#define MOUSE_H

#include "buttons.h"
#include <vector2.h>

#include <cstdint>

class Mouse
{
public:
	Mouse() = default;
	Mouse(const Mouse& that) = default;
	Mouse(Mouse&& that) = default;
	Mouse& operator=(const Mouse& rhs) = default;
	Mouse& operator=(Mouse&& rhs) = default;
	void Update();
	const bool IsButtonUp(MouseButtons button);
	const bool IsButtonDown(MouseButtons button);
	const bool IsButtonPressed(MouseButtons button);
	const Vector2<int> Position() { return position; };

private:
	Vector2<int> position = Vector2<int>::Zero();
	uint32_t mouseState = 0;
	uint32_t oldMouseState = 0;
};
#endif