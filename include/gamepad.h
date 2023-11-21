#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "api.h"
#include "buttons.h"
#include "vector2.h"

class KARAKURI_API Gamepad
{
public:
	Gamepad(int index);
	void Udpate();
	bool IsButtonDown(GamePadButtons button);
	bool IsButtonUp(GamePadButtons button);
	const float LeftTrigger();
	const float RightTrigger();
	const Vector2<float> LeftThumbStick(const float deadzone);
	const Vector2<float> RightThumbStick(const float deadzone);
	const bool IsConnected() { return isConnected; };
	const void Vibrate(float leftMotor, float rightMotor, int duration);

	friend class Game;

private:
	int index;
	bool isConnected;
	const int axisLimit;
	const int negativeAxisLimit;
};

#endif