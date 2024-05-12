#ifndef KEYBOARD_COMBO_H
#define KEYBOARD_COMB0_H

#include <vector>
#include "keys.h"

class KeyboardCombo
{
public:
	KeyboardCombo(const KeyboardCombo& that) = default;
	KeyboardCombo(KeyboardCombo&& that) = default;
	KeyboardCombo& operator=(const KeyboardCombo& rhs) = default;
	KeyboardCombo& operator=(KeyboardCombo&& rhs) = default;

	KeyboardCombo(const float inputTime, const std::vector<Keys>& combo);

	const float InputTime() const { return inputTime; }
	const std::vector<Keys>& Combo() const { return combo; }

private:
	const float inputTime;	
	const std::vector<Keys>& combo;
};

#endif // !KEYBOARD_COMBO_H