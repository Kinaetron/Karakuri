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

const float Gamepad::LeftTrigger() {
	return (float)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) / axisLimit;
}
const float Gamepad::RightTrigger() {
	return (float)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) / axisLimit;
}

const Vector2<float> Gamepad::LeftThumbStick(float deadzone)
{
	float x_axis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
	float y_axis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);

	x_axis = x_axis > 0 ? x_axis / axisLimit : x_axis / negativeAxisLimit;
	y_axis = y_axis > 0 ? y_axis / axisLimit : y_axis / negativeAxisLimit;

	Vector2<float> stickInput = Vector2<float>(x_axis, y_axis);

	if (stickInput.Length() < deadzone) {
		stickInput = Vector2<float>::Zero();
	}

	return stickInput;
}

const Vector2<float> Gamepad::RightThumbStick(float deadzone)
{
	float x_axis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
	float y_axis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);

	x_axis = x_axis > 0 ? x_axis / axisLimit : x_axis / negativeAxisLimit;
	y_axis = y_axis > 0 ? y_axis / axisLimit : y_axis / negativeAxisLimit;

	Vector2<float> stickInput = Vector2<float>(x_axis, y_axis);

	if (stickInput.Length() < deadzone) {
		stickInput = Vector2<float>::Zero();
	}

	return stickInput;
}

const void Gamepad::Vibrate(float leftMotor, float rightMotor, int duration)
{
	const int limit = 65535;

	uint16_t leftIntensity = (uint16_t)(leftMotor * limit);
	uint16_t rightIntensity = (uint16_t)(rightMotor * limit);

	SDL_GameControllerRumble(
		controller, 
    leftIntensity, 
   rightIntensity, 
			duration);
}