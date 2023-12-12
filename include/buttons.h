#ifndef BUTTONS_H
#define BUTTONS_H

#include <cstdint>

enum class GamePadButtons : uint8_t
{
	FACE_DOWN = 0,
	FACE_RIGHT = 1,
	FACE_LEFT = 2,
	FACE_UP = 3,
	SELECT = 4,
	GUIDE = 5,
	START = 6,
	LEFT_STICK = 7,
	RIGHT_STICK = 8,
	LEFT_BUMPER = 9,
	RIGHT_BUMPER = 10,
	DPAD_UP = 11,
	DPAD_DOWN = 12,
	DPAD_LEFT = 13,
	DPAD_RIGHT = 14,
	BUTTON_MAX = 15
};


enum class MouseButtons : uint32_t
{
	LEFT = 1,
	MIDDLE = 2,
	RIGHT = 3
};
#endif