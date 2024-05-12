#include <SDL.h>
#include "keyboard.h"
#include "combo_listener.h"
#include <spdlog/spdlog.h>

ComboListener::ComboListener(const int playerIndex):
	timePassed(0),
	playerIndex(playerIndex),
	controller(nullptr)
{
}

void ComboListener::Update(const float millisecondUpdate)
{
	timePassed += millisecondUpdate;

	oldKeyboardState = keyboardState;
	std::vector<Keys> keysPressed{};
	const uint8_t* state = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < Keyboard::NumKeys(); ++i) {
		keyboardState[i] = state[i];
	}

	for (int key = 0; key < Keyboard::NumKeys(); ++key)
	{
		if (keyboardState[(uint8_t)key] == 1 &&
			oldKeyboardState[(uint8_t)key] == 0) 
		{
			keysPressed.push_back((Keys)key);
		}
	}

	keyboardInputBuffer.push_back(ButtonsPressedFrame(timePassed, keysPressed));

	controller = SDL_GameControllerOpen(playerIndex);

	if (controller == nullptr) {
		return;
	}

	oldGamePadState = gamePadState;
	std::vector<GamePadButtons> buttonsPressed {};

	for (uint8_t button = 0; button < SDL_CONTROLLER_BUTTON_MAX; ++button)
	{
		uint8_t buttonState = SDL_GameControllerGetButton(controller, (SDL_GameControllerButton)button);
		gamePadState[button] = buttonState;

		if (gamePadState[(uint8_t)button] == 1 &&
			oldGamePadState[(uint8_t)button] == 0)
		{
			buttonsPressed.push_back((GamePadButtons)button);
		}
	}

	controllerInputBuffer.push_back(ButtonsPressedFrame(timePassed, buttonsPressed));
}

const bool ComboListener::ComboExecuted(const KeyboardCombo& combo)
{
	float timeCheckAgainst = timePassed - combo.InputTime();
	std::vector<Keys> keysPressed;

	for (int i = 0; i < keyboardInputBuffer.size(); i++)
	{

		if (keyboardInputBuffer[i].TimeStamp() >= timeCheckAgainst)
		{
			for (int j = 0; j < keyboardInputBuffer[i].KeysPressed().size(); j++) {
				keysPressed.push_back(keyboardInputBuffer[i].KeysPressed()[j]);
			}
		}
	}

	if (keysPressed.empty() ||
		combo.Combo().size() > keysPressed.size())
	{
		return false;
	}

	int min = 0;
	int max = combo.Combo().size();
	bool matchFound = false;

	while (max <= keysPressed.size())
	{
		for (int i = min; i < max; i++)
		{
			matchFound = true;

			if (combo.Combo()[i] != keysPressed[i])
			{
				min++;
				max++;
				matchFound = false;
				break;
			}
		}

		return matchFound;
	}

	return false;
}

const bool ComboListener::ComboExecuted(const ControllerCombo& combo)
{
	float timeCheckAgainst = timePassed - combo.InputTime();
	std::vector<GamePadButtons> buttonsPressed;

	for (int i = 0; i < controllerInputBuffer.size(); i++)
	{

		if(controllerInputBuffer[i].TimeStamp() >= timeCheckAgainst)
		{
			for (int j = 0; j < controllerInputBuffer[i].ButtonsPressed().size(); j++) {
				buttonsPressed.push_back(controllerInputBuffer[i].ButtonsPressed()[j]);
			}
		}
	}

	if (buttonsPressed.empty() || 
		combo.Combo().size() > buttonsPressed.size()) 
	{
		return false;
	}

	int min = 0;
	int max = combo.Combo().size();
	bool matchFound = false;

	while(max <= buttonsPressed.size())
	{
		for (int i = min; i < max; i++)
		{
			matchFound = true;

			if (combo.Combo()[i] != buttonsPressed[i]) 
			{
				min++;
				max++;
				matchFound = false;
				break;
			}
		}

		return matchFound;
	}

	return false;
}

ComboListener::ButtonsPressedFrame::ButtonsPressedFrame(
	float timeStamp, 
	std::vector<GamePadButtons> buttonsPressed): 
	timeStamp(timeStamp),
	buttonsPressed(buttonsPressed)
{
}

ComboListener::ButtonsPressedFrame::ButtonsPressedFrame(
	float timeStamp,
	std::vector<Keys> keysPressed) :
	timeStamp(timeStamp),
	keysPressed(keysPressed)
{
}
