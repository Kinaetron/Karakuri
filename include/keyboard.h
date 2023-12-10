#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "keys.h"
#include <array>
#include <cstdint>

class Keyboard
{
public:
	Keyboard() = default;
	Keyboard(const Keyboard& that) = default;
	Keyboard(Keyboard&& that) = default;
	Keyboard& operator=(const Keyboard& rhs) = default;
	Keyboard& operator=(Keyboard&& rhs) = default;
	void Update();
	const bool IsKeyDown(Keys key) const;
	const bool IsKeyUp(Keys key) const;
	const bool IsKeyPressed(Keys key) const;

private:
	std::array<uint8_t, 512> keyboardState {};
	std::array<uint8_t, 512> oldKeyboardState {};
};

#endif