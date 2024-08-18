#include "update_manager.h"
#include "keyboard.h"
#include <iostream>
#include <SDL.h>

Keyboard::Keyboard() {
	UpdateManager::Add(this);
}

Keyboard::~Keyboard() {
	UpdateManager::Remove(this);
}

void Keyboard::Update(float millisecondsPerUpdate)
{
	oldKeyboardState = keyboardState;

	const uint8_t* state = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < Keyboard::NumKeys(); ++i) {
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