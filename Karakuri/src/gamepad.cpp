#include "../include/gamepad.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "../include/vector2.h"


SDL_GameController* controller;

Gamepad::Gamepad(int index):
	index(index),
	isConnected(false),
	axisLimit(32767),
	negativeAxisLimit(32768)

{
}

void Gamepad::Udpate()
{
	controller = SDL_GameControllerOpen(index);
	isConnected = !controller == NULL;
}

bool Gamepad::IsButtonDown(GamePadButtons button) {
	return SDL_GameControllerGetButton(controller, (SDL_GameControllerButton)button);
}

bool Gamepad::IsButtonUp(GamePadButtons button) {
	return !SDL_GameControllerGetButton(controller, (SDL_GameControllerButton)button);
}

const double Gamepad::LeftTrigger() {
	return (double)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) / axisLimit;
}
const double Gamepad::RightTrigger() {
	return (double)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) / axisLimit;
}

const Vector2<float> Gamepad::LeftThumbStick(double deadzone)
{
	double x_axis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
	double y_axis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);

	x_axis = x_axis > 0 ? x_axis / axisLimit : x_axis / negativeAxisLimit;
	y_axis = y_axis > 0 ? y_axis / axisLimit : y_axis / negativeAxisLimit;

	Vector2<float> stickInput = Vector2<float>(x_axis, y_axis);

	if (stickInput.Length() < deadzone) {
		stickInput = Vector2<float>::Zero();
	}

	return stickInput;
}

const Vector2<float> Gamepad::RightThumbStick(double deadzone)
{
	double x_axis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
	double y_axis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);

	x_axis = x_axis > 0 ? x_axis / axisLimit : x_axis / negativeAxisLimit;
	y_axis = y_axis > 0 ? y_axis / axisLimit : y_axis / negativeAxisLimit;

	Vector2<float> stickInput = Vector2<float>(x_axis, y_axis);

	if (stickInput.Length() < deadzone) {
		stickInput = Vector2<float>::Zero();
	}

	return stickInput;
}