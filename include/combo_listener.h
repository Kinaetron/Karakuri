#ifndef COMBO_LISTENER_H
#define COMBO_LISTENER_H

#include <vector>
#include <array>
#include "keyboard_combo.h"
#include "controller_combo.h"

struct _SDL_GameController;
typedef struct _SDL_GameController SDL_GameController;

class ComboListener
{
public:
	ComboListener(const ComboListener& that) = default;
	ComboListener(ComboListener&& that) = default;
	ComboListener& operator=(const ComboListener& rhs) = default;
	ComboListener& operator=(ComboListener&& rhs) = default;

	ComboListener(const int playerIndex);
	void Update(const float millisecondUpdate);
	const bool ComboExecuted(const KeyboardCombo& combo);
	const bool ComboExecuted(const ControllerCombo& combo);

private:
	class ButtonsPressedFrame
	{
	public:
		ButtonsPressedFrame(const ButtonsPressedFrame& that) = default;
		ButtonsPressedFrame(ButtonsPressedFrame&& that) = default;
		ButtonsPressedFrame& operator=(const ButtonsPressedFrame& rhs) = default;
		ButtonsPressedFrame& operator=(ButtonsPressedFrame&& rhs) = default;

		ButtonsPressedFrame(float timeStamp, std::vector<Keys> buttonsPressed);
		ButtonsPressedFrame(float timeStamp, std::vector<GamePadButtons> buttonsPressed);

		float TimeStamp() const { return timeStamp; }

		std::vector<Keys>& KeysPressed() { return keysPressed; }
		std::vector<GamePadButtons>& ButtonsPressed() { return buttonsPressed; }

	private:
		float timeStamp;
		std::vector<Keys> keysPressed;
		std::vector<GamePadButtons> buttonsPressed;
	};

	float timePassed;
	const int playerIndex;
	SDL_GameController* controller;
	std::array<uint8_t, 21> gamePadState{};
	std::array<uint8_t, 21> oldGamePadState{};
	std::array<uint8_t, 512> keyboardState{};
	std::array<uint8_t, 512> oldKeyboardState{};

	std::vector<ButtonsPressedFrame> keyboardInputBuffer;
	std::vector<ButtonsPressedFrame> controllerInputBuffer;
};

#endif // !COMBO_LISTENER_H