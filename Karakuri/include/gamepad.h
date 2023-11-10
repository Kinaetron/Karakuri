#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "api.h"
#include "buttons.h"
#include "glm/glm.hpp"

class KARAKURI_API Gamepad
{
public:
	Gamepad(int index);
	void Udpate();
	bool IsButtonDown(GamePadButtons button);
	bool IsButtonUp(GamePadButtons button);
	const double LeftTrigger();
	const double RightTrigger();
	const glm::vec2 LeftThumbStick(double deadzone);
	const glm::vec2 RightThumbStick(double deadzone);
	const bool IsConnected() { return isConnected; };

	friend class Game;

private:
	int index;
	bool isConnected;
	const int axisLimit;
	const int negativeAxisLimit;
};

#endif