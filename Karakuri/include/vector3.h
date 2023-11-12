#ifndef VECTOR3_H
#define VECTOR3_H

#include "api.h"
#include <math.h>
#include <type_traits>

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
class KARAKURI_API Vector3
{
public:
	T X;
	T Y;
	T Z;

	Vector3(T x, T y, T z) :
		X(x),
		Y(y),
		Z(z)
	{
	}

	Vector3() :
		X(0),
		Y(0),
		Z(0)
	{
	}

	static Vector3 Zero() {
		return Vector3();
	}

	Vector3& operator = (const Vector3& value)
	{
		X = value.X;
		Y = value.Y;
		Z = value.Z;

		return *this;
	}

	bool operator == (const Vector3& value) const {
		return X == value.X && Y == value.Y && Z == value.Z;
	}

	bool operator != (const Vector3& value) const {
		return !(*this == value);
	}

	Vector3 operator + (const Vector3& value) const
	{
		Vector3 result;
		result.X = X + value.X;
		result.Y = Y + value.Y;
		result.Z = Z + value.Z;

		return result;
	}

	Vector3 operator - (const Vector3& value) const
	{
		Vector3 result;
		result.X = X - value.X;
		result.Y = Y - value.Y;
		result.Z = Z - value.Z;

		return result;
	}

	template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
	Vector3 operator * (const U number) const
	{
		Vector3 result;
		result.X = X * number;
		result.Y = Y * number;
		result.Z = Z * number;

		return result;
	}

	template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
	Vector3 operator / (const U number) const
	{
		Vector3 result;
		result.X = X / number;
		result.Y = Y / number;
		result.Z = Z / number;

		return result;
	}

	Vector3& operator += (const Vector3& value) const
	{
		X += value.X;
		Y += value.Y;
		Z += value.Z;

		return *this;
	}

	Vector3& operator -= (const Vector3& value) const
	{
		X -= value.X;
		Y -= value.Y;
		Z += value.Z;

		return *this;
	}

	Vector3& operator *= (const Vector3& value) const
	{
		X *= value.X;
		Y *= value.Y;
		Z *= value.Z;

		return *this;
	}

	Vector3& operator /= (const Vector3& value) const
	{
		X /= value.X;
		Y /= value.Y;
		Z /= value.Z;

		return *this;
	}

	T Length() const {
		return sqrt(X * X + Y * Y + Z * Z);
	}

	Vector3& Normalize() const
	{
		float length = Length();
		if (length != 0) 
		{
			this->X /= length;
			this->Y /= length;
			this->Z /= length;
		}
		return *this;
	}

	Vector3 Normal() const {
		return Vector3(Y, -X).Normalize();
	}

	T Dot(const Vector3 value) const {
		return (X * value.X) + (Y * value.Y);
	}
};

#endif