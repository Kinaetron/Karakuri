#ifndef MOUSE_H
#define MOUSE_H

#include "buttons.h"
#include <vector2.h>

#include <cstdint>

class Mouse
{
public:
	Mouse();
	Mouse(const Mouse& that) = default;
	Mouse(Mouse&& that) = default;
	Mouse& operator=(const Mouse& rhs) = default;
	Mouse& operator=(Mouse&& rhs) = default;
	void Update();
	const bool IsButtonUp(MouseButtons button) const;
	const bool IsButtonDown(MouseButtons button) const;
	const bool IsButtonPressed(MouseButtons button) const;
	const Vector2<int> Position() const { return position; };

private:
	Vector2<int> position;
	uint32_t mouseState;
	uint32_t oldMouseState;
};
#endif