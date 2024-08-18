#include <mouse.h>
#include <SDL.h>

Mouse::Mouse():
	position(Vector2<int>::Zero()),
	mouseState(0),
	oldMouseState(0)
{
}

void Mouse::Update(float millisecondsPerUpdate)
{
	oldMouseState = mouseState;
	mouseState = SDL_GetMouseState(&position.X, &position.Y);
}

const bool Mouse::IsButtonUp(MouseButtons button) const {
	return !(mouseState & SDL_BUTTON((uint32_t)button));
}

const bool Mouse::IsButtonDown(MouseButtons button) const {
	return  mouseState & SDL_BUTTON((uint32_t)button);
}

const bool Mouse::IsButtonPressed(MouseButtons button) const
{
	return (mouseState & SDL_BUTTON((uint32_t)button)) == 1 &&
		   (oldMouseState & SDL_BUTTON((uint32_t)button)) == 0;
}