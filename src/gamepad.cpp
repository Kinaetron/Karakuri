#include <gamepad.h>
#include <SDL.h>
#include <iostream>
#include <vector2.h>

Gamepad::Gamepad(int index):
	index(index),
	isConnected(false),
	axisLimit(32767),
	negativeAxisLimit(32768),
	controller(nullptr)
{
}

void Gamepad::Udpate()
{
	controller = SDL_GameControllerOpen(index);
	isConnected = !controller == NULL;

	if (isConnected)
	{
		oldGamePadState = gamePadState;

		for (uint8_t button = 0; button < SDL_CONTROLLER_BUTTON_MAX; ++button) 
		{
			uint8_t buttonState = SDL_GameControllerGetButton(controller, (SDL_GameControllerButton)button);
			gamePadState[button] = buttonState;
		}
	}
}

const bool Gamepad::IsButtonDown(GamePadButtons button)  {
	return gamePadState[(uint8_t)button] != 0;
}

const bool Gamepad::IsButtonUp(GamePadButtons button)  {
	return gamePadState[(uint8_t)button] == 0;
}

const bool Gamepad::IsButtonPressed(GamePadButtons button)
{
	return	gamePadState[(uint8_t)button] == 1 && 
		    oldGamePadState[(uint8_t)button] == 0;
}

const float Gamepad::LeftTrigger() const {
	return static_cast<float>(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) / axisLimit);
}
const float Gamepad::RightTrigger() const {
	return static_cast<float>(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) / axisLimit);
}

const Vector2<float> Gamepad::LeftThumbStick(float deadzone) const
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

const Vector2<float> Gamepad::RightThumbStick(float deadzone) const
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

	uint16_t leftIntensity = static_cast<uint16_t>(leftMotor * limit);
	uint16_t rightIntensity = static_cast<uint16_t>(rightMotor * limit);

	SDL_GameControllerRumble(
		controller, 
    leftIntensity, 
   rightIntensity, 
			duration);
}