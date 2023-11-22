#include "../include/keyboard.h"
#include <iostream>
#include <SDL.h>

Keyboard::Keyboard()
{
	std::fill(keyboardState.begin(), keyboardState.end(), 0);
	std::fill(oldKeyboardState.begin(), oldKeyboardState.begin(), 0);
}

void Keyboard::Update() 
{
	oldKeyboardState = keyboardState;

	const uint8_t* state = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
		keyboardState[i] = state[i];
	}
}

const bool Keyboard::IsKeyDown(Keys key) const {
	return static_cast<bool>(keyboardState[(uint8_t)key]);
}

const bool Keyboard::IsKeyUp(Keys key) const {
	return !static_cast<bool>(keyboardState[(uint8_t)key]);
}

const bool Keyboard::IsKeyPressed(Keys key) const
{
	return static_cast<bool>(keyboardState[(uint8_t)key]) &&
		  !static_cast<bool>(oldKeyboardState[(uint8_t)key]);
}