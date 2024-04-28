#include <SDL.h>
#include "combo_listener.h"

ComboListener::ComboListener(const int playerIndex):
	timePassed(0),
	playerIndex(playerIndex),
	controller(nullptr)
{
}

void ComboListener::Update(const float millisecondUpdate)
{
	controller = SDL_GameControllerOpen(playerIndex);

	if (controller == nullptr) {
		return;
	}

	timePassed += millisecondUpdate;

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

	inputBuffer.push_back(ButtonsPressedFrame(timePassed, buttonsPressed));
}

const bool ComboListener::ComboExecuted(const ControllerCombo& combo)
{
	float timeCheckAgainst = timePassed - combo.InputTime();
	std::vector<GamePadButtons> buttonsPressed;

	for (int i = 0; i < inputBuffer.size(); i++)
	{

		if(inputBuffer[i].TimeStamp() >= timeCheckAgainst)
		{
			for (int j = 0; j < inputBuffer[i].ButtonsPressed().size(); j++) {
				buttonsPressed.push_back(inputBuffer[i].ButtonsPressed()[j]);
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
