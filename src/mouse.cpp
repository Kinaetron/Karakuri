#include <mouse.h>
#include <SDL.h>

Mouse::Mouse()
	: mouseState(0),
	  oldMouseState(0),
	  position(Vector2<int>(0, 0))
{
}

void Mouse::Update() 
{
	oldMouseState = mouseState;
	mouseState = SDL_GetMouseState(&position.X, &position.Y);
}

const bool Mouse::IsButtonUp(MouseButtons button) {
	return !(mouseState & SDL_BUTTON((uint32_t)button));
}

const bool Mouse::IsButtonDown(MouseButtons button) {
	return  mouseState & SDL_BUTTON((uint32_t)button);
}

const bool Mouse::IsButtonPressed(MouseButtons button)
{
	return (mouseState & SDL_BUTTON((uint32_t)button)) == 1 &&
		   (oldMouseState & SDL_BUTTON((uint32_t)button)) == 0;
}