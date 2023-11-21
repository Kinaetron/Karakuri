#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "api.h"
#include "keys.h"
#include <cstdint>

class KARAKURI_API Keyboard
{
public:
	Keyboard();
	~Keyboard();
	void Update();
	const bool IsKeyDown(Keys key) const;
	const bool IsKeyUp(Keys key) const;

private:
	uint8_t* keyboardState;
};

#endif