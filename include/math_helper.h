#ifndef MATH_HELPER_H
#define MATH_HELPER_H

class MathHelper
{
public:

	/*
	* Sends the signed variant of a number.
	* \param gets the signed value of this number.
	* \returns either -1, 0 or 1 depending on the sign of the number.
	*/
	static int Sign(int number) {
		return (number > 0) ? 1 : ((number < 0) ? -1 : 0);
	}
};
#endif