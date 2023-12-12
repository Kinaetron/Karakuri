#ifndef MATH_UTILITY_H
#define MATH_UTILITY_H

#include <type_traits>

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
class MathUtility
{
public:
	static T Sign(T x)
	{
		if (x > 0) {
			return static_cast<T>(1);
		}

		if (x < 0) {
			return static_cast<T>(-1);
		}

		return static_cast<T>(0);
	}
};

#endif