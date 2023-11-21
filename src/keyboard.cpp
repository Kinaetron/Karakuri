#include "../include/keyboard.h"
#include <iostream>
#include <SDL.h>

Keyboard::Keyboard():
	keyboardState(nullptr)
{
}

void Keyboard::Update() {
	keyboardState = (uint8_t*)SDL_GetKeyboardState(NULL);
}

const bool Keyboard::IsKeyDown(Keys key) const {
	return keyboardState[(uint8_t)key];
}

const bool Keyboard::IsKeyUp(Keys key) const {
	return !keyboardState[(uint8_t)key];
}

Keyboard::~Keyboard() {
	delete[] keyboardState;
}