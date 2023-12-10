#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "buttons.h"
#include "vector2.h"
#include <array>

class Gamepad
{
public:
	Gamepad() = default;
	Gamepad(const Gamepad& that) = default;
	Gamepad(Gamepad&& that) = default;
	Gamepad& operator=(const Gamepad& rhs) = default;
	Gamepad& operator=(Gamepad&& rhs) = default;
	Gamepad(int index);
	void Udpate();
	const bool IsButtonDown(GamePadButtons button);
	const bool IsButtonUp(GamePadButtons button);
	const bool IsButtonPressed(GamePadButtons button);
	const float LeftTrigger();
	const float RightTrigger();
	const Vector2<float> LeftThumbStick(float deadzone);
	const Vector2<float> RightThumbStick(float deadzone);
	const bool IsConnected() { return isConnected; };
	const void Vibrate(float leftMotor, float rightMotor, int duration);

private:
	int index = 0;
	std::array<uint8_t, 21> gamePadState {};
	std::array<uint8_t, 21> oldGamePadState {};
	bool isConnected = false;
	int axisLimit = 0;
	int negativeAxisLimit = 0;
};

#endif