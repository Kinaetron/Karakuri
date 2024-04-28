#ifndef CONTROLLER_COMBO_H
#define CONTROLLER_COMBO_H

#include <vector>
#include "buttons.h"

class ControllerCombo
{
public:
	ControllerCombo(const ControllerCombo& that) = default;
	ControllerCombo(ControllerCombo&& that) = default;
	ControllerCombo& operator=(const ControllerCombo& rhs) = default;
	ControllerCombo& operator=(ControllerCombo&& rhs) = default;

	ControllerCombo(const float inputTime, const std::vector<GamePadButtons>& combo);

	const float InputTime() const { return inputTime; }
	const std::vector<GamePadButtons>& Combo() const { return combo; }

private:
	const float inputTime;
	const std::vector<GamePadButtons>& combo;
};

#endif