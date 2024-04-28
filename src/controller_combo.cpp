#include "controller_combo.h"

ControllerCombo::ControllerCombo(const float inputTime, const std::vector<GamePadButtons>& combo):
	inputTime(inputTime),
	combo(combo)
{
}