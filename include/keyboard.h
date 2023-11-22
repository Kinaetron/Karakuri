#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "api.h"
#include "keys.h"
#include <array>
#include <cstdint>

class KARAKURI_API Keyboard
{
public:
	Keyboard();
	void Update();
	const bool IsKeyDown(Keys key) const;
	const bool IsKeyUp(Keys key) const;
	const bool IsKeyPressed(Keys key) const;

private:
	std::array<uint8_t, 512> keyboardState;
	std::array<uint8_t, 512> oldKeyboardState;
};

#endif