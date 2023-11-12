#ifndef VECTOR2_H
#define VECTOR2_H

#include "api.h"
#include <math.h>
#include <type_traits>

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
class KARAKURI_API Vector2
{
public:
	T X;
	T Y;

	Vector2(T x, T y):
		X(x), 
		Y(y) 
	{ 
	}

	Vector2():
		X(0), 
		Y(0) 
	{
	}

	static Vector2 Zero() {
		return Vector2();
	}

	Vector2& operator = (const Vector2& value)
	{
		X = value.X;
		Y = value.Y;
		return *this;
	}

	bool operator == (const Vector2& value) const {
		return X == value.X && Y == value.Y;
	}

	bool operator != (const Vector2& value) const {
		return !(*this == value);
	}

	Vector2 operator + (const Vector2& value) const 
	{
		Vector2 result;
		result.X = X + value.X;
		result.Y = Y + value.Y;

		return result;
	}

	Vector2 operator - (const Vector2& value) const
	{
		Vector2 result;
		result.X = X - value.X;
		result.Y = Y - value.Y;

		return result;
	}

	template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
	Vector2 operator * (const U number) const
	{
		Vector2 result;
		result.X = X * number;
		result.Y = Y * number;

		return result;
	}

	template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
	Vector2 operator / (const U number) const
	{
		Vector2 result;
		result.X = X / number;
		result.Y = Y / number;

		return result;
	}

	Vector2& operator += (const Vector2& value) const
	{
		X += value.X;
		Y += value.Y;

		return *this;
	}

	Vector2& operator -= (const Vector2& value) const
	{
		X -= value.X;
		Y -= value.Y;

		return *this;
	}

	Vector2& operator *= (const Vector2& value) const
	{
		X *= value.X;
		Y *= value.Y;

		return *this;
	}

	Vector2& operator /= (const Vector2& value) const
	{
		X /= value.X;
		Y /= value.Y; 

		return *this;
	}

	T Length() const {
		return sqrt(X * X + Y * Y);
	}

	Vector2& Normalize()
	{
		float length = Length();
		if (length != 0) 
		{
			this->X /= length;
			this->Y /= length;
		}
		return *this;
	}

	Vector2 Normal() const {
		return Vector2(Y, -X).Normalize();
	}

	T Dot(const Vector2 value) const {
		return (X * value.X) + (Y * value.Y);
	}
};

#endif