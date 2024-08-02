#ifndef MATH_UTILITY_H
#define MATH_UTILITY_H

#include <type_traits>

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
class MathUtility
{
public:
	/*
	* Sends the signed variant of a number.
	* \param gets the signed value of this number.
	* \returns either -1, 0 or 1 depending on the sign of the number.
	*/
	static T Sign(T number) {
		return (number > 0) ? 1 : ((number < 0) ? -1 : 0);
	}
};

#endif