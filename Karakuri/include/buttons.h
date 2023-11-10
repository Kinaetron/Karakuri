#ifndef BUTTONS_H
#define BUTTONS_H

#include "api.h"

enum class KARAKURI_API Buttons : int
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

#endif