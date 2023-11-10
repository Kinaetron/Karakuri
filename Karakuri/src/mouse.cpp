#include "../include/mouse.h"
#include <SDL2/SDL.h>

Mouse::Mouse()
	: mouseState(0),
	  position(glm::ivec2(0, 0))
{
}

void Mouse::Update() {
	mouseState = SDL_GetMouseState(&position.x, &position.y);
}

const bool Mouse::IsButtonUp(MouseButtons button) {
	return !(mouseState & SDL_BUTTON((uint32_t)button));
}

const bool Mouse::IsButtonDown(MouseButtons button) {
	return  mouseState & SDL_BUTTON((uint32_t)button);
}