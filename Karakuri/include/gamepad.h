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
	const double LeftTrigger();
	const double RightTrigger();
	const Vector2<float> LeftThumbStick(double deadzone);
	const Vector2<float> RightThumbStick(double deadzone);
	const bool IsConnected() { return isConnected; };

	friend class Game;

private:
	int index;
	bool isConnected;
	const int axisLimit;
	const int negativeAxisLimit;
};

#endif