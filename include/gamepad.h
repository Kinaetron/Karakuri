#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "buttons.h"
#include "vector2.h"
#include "update_component.h"
#include <array>

struct _SDL_GameController;
typedef struct _SDL_GameController SDL_GameController;

class Gamepad: public UpdateComponent
{
public:
	Gamepad(const Gamepad& that) = default;
	Gamepad(Gamepad&& that) = default;
	Gamepad& operator=(const Gamepad& rhs) = default;
	Gamepad& operator=(Gamepad&& rhs) = default;

	/*
	* Creates an object that represents a game pad.
	* \param index, selects the controller port to for the game pad to use.
	*/
	Gamepad(int index);

	~Gamepad();

	/*
	* Checks the current state of the controller. Call this method in the game update method.
	*/
	void Update(float millisecondsPerUpdate) override;

	/*
	* Gets if the button is down on the controller.
	* \param button, specifics which button to check for.
	* \return bool that tells if the button is down.
	*/
	const bool IsButtonDown(GamePadButtons button);

	/*
	* Gets if the button is up on the controller.
	* \param button, specifics which button to check for.
	* \return bool that tells if the button is up.
	*/
	const bool IsButtonUp(GamePadButtons button);

	/*
	* Gets if the button is pressed on the controller, specifically if the button is down on first frame and up on the next.
	* \param button, specifics which button to check for.
	* \return bool that tells if the button is pressed.
	*/
	const bool IsButtonPressed(GamePadButtons button);

	/*
	* Check to see if the left trigger on the controller is pressed or not.
	* \return a value from 0.0f to 1.0f which represents the how much the trigger is pressed.
	*/
	const float LeftTrigger() const;

	/*
	* Check to see if the right trigger on the controller is pressed or not.
	* \return a value from 0.0f to 1.0f which represents the how much the trigger is pressed.
	*/
	const float RightTrigger() const;

	/*
	* Get the position of the left thumbstick.
	* \param deadzone is a set size on the thumbstick to ignore.
	* \return a value from 0.0f to 1.0f which is represents the position of the stick.
	*/
	const Vector2<float> LeftThumbStick(float deadzone) const;

	/*
	* Get the position of the right thumbstick.
	* \param deadzone is a set size on the thumbstick to ignore.
	* \return a value from 0.0f to 1.0f which is represents the position of the stick.
	*/
	const Vector2<float> RightThumbStick(float deadzone) const;

	/*
	* Get if the controller is connected.
	* \return a bool if the controller is connected.
	*/
	const bool IsConnected() const { return isConnected; };

	/*
	* Set the vibration of the controller.
	* \param leftMotor sets the power of the left motor using a value from 0.0f to 1.0f.
	* \param rightMotor sets the power of the right motor using a value from 0.0f to 1.0f.
	* \param duration sets the how long the vibration goes on for in milliseconds.
	*/
	const void Vibrate(float leftMotor, float rightMotor, int duration);

private:
	int index = 0;
	std::array<uint8_t, 21> gamePadState {};
	std::array<uint8_t, 21> oldGamePadState {};
	SDL_GameController* controller;
	bool isConnected;
	int axisLimit;
	int negativeAxisLimit;
};

#endif