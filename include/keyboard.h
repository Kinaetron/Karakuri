#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "keys.h"
#include "update_component.h"
#include <array>
#include <cstdint>

class Keyboard: protected UpdateComponent
{
public:
	/*
	* Creates the keyboard object.
	*/
	Keyboard();
	Keyboard(const Keyboard& that) = default;
	Keyboard(Keyboard&& that) = default;
	Keyboard& operator=(const Keyboard& rhs) = default;
	Keyboard& operator=(Keyboard&& rhs) = default;
	~Keyboard();

	/*
	* Gets if the key is down on the keyboard.
	* \param key, specifics which key to check for.
	* \return bool that tells if the key is down.
	*/
	const bool IsKeyDown(Keys key) const;

	/*
	* Gets if the key is up on the keyboard.
	* \param key, specifics which key to check for.
	* \return bool that tells if the key is down.
	*/
	const bool IsKeyUp(Keys key) const;

	/*
	* Gets if the key is pressed on the controller, specifically if the key is down on first frame and up on the next.
	* \param key, specifics which key to check for.
	* \return bool that tells if the key is pressed.
	*/
	const bool IsKeyPressed(Keys key) const;

	const int static NumKeys() { return 231; }

private:
	void Update(float millisecondsPerUpdate) override;

private:
	std::array<uint8_t, 512> keyboardState {};
	std::array<uint8_t, 512> oldKeyboardState {};
};

#endif