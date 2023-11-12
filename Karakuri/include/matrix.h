#ifndef MATRIX_H
#define MATRIX_H

#include "api.h"
#include <math.h>
#include <type_traits>
#include "../include/vector3.h"

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
class KARAKURI_API Matrix
{
public:
	T M[4][4];

	Matrix()
	{
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++) {
				M[i][j] = 0.0;
			}
		}
	}

    static Matrix OrthographicProjection(T left, T right, T bottom, T top, T near, T far)
	{
		Matrix result;

		result.M[0][0] = 2.0f / (right - left);
		result.M[1][1] = 2.0f / (top - bottom);
		result.M[2][2] = -2.0f / (far - near);
		result.M[3][0] = -(right + left) / (right - left);
		result.M[3][1] = -(top + bottom) / (top - bottom);
		result.M[3][2] = -(far + near) / (far - near);
		result.M[3][3] = 1.0f;

		return result;
	}

	static Matrix Identity()
	{
		Matrix result;
		result.M[0][0] = 1;
		result.M[1][1] = 1;
		result.M[2][2] = 1;
		result.M[3][3] = 1;

		return result;
	}

	Matrix& Translate(Vector3<T> vector)
	{
		this->M[0][3] += vector.X;
		this->M[1][3] += vector.Y;
		this->M[2][3] += vector.Z;

		return *this;
	}

	Matrix& Rotate(T angle)
	{
		float c = cos(angle);
		float s = sin(angle);

		this->M[0][0] = c;
		this->M[0][1] = -s;
		this->M[1][0] = s;
		this->M[1][1] = c;

		return *this;
	}

	Matrix& Scale(Vector3<T> vector)
	{
		this->M[0][0] = vector.X;
		this->M[1][1] = vector.Y;
		this->M[2][2] = vector.Z;

		return *this;
	}
};

#endif