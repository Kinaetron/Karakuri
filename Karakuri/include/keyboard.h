#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "api.h"
#include <cstdint>

class KARAKURI_API Keyboard
{
public:
	Keyboard();
	void Update();
	const bool IsKeyDown(int keycode) const;
	const bool IsKeyUp(int keycode) const;

private:
	uint8_t* keyboardState;
};

#endif
