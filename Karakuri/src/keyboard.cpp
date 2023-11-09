#include "../include/keyboard.h"
#include <iostream>
#include <SDL2/SDL.h>

Keyboard::Keyboard():
	keyboardState(NULL)
{
}

void Keyboard::Update() {
	keyboardState = (uint8_t*)SDL_GetKeyboardState(NULL);
}

const bool Keyboard::IsKeyDown(int keycode) const {
	return keyboardState[keycode];
}

const bool Keyboard::IsKeyUp(int keycode) const {
	return !keyboardState[keycode];
}