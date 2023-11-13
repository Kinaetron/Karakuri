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

	Matrix& operator = (const Matrix& matrix)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++) {
				M[i][j] = matrix.M[i][j];
			}
		}

		return *this;
	}

	Matrix operator * (const Matrix matrix) const
	{
		Matrix result;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.M[i][j] = 
					this->M[i][0] * matrix.M[0][j] +
					this->M[i][1] * matrix.M[1][j] +
					this->M[i][2] * matrix.M[2][j] +
					this->M[i][3] * matrix.M[3][j];
			}
		}

		return result;
	}

    static Matrix OrthographicProjection(T left, T right, T bottom, T top, T near, T far)
	{
		Matrix result = Identity();

		result.M[0][0] = 2.0f / (right - left);   result.M[1][0] = 0.0f;                    result.M[2][0] = 0.0f;                    result.M[3][0] = 0.0f;
		result.M[0][1] = 0.0f;                    result.M[1][1] = 2.0f / (top - bottom);   result.M[2][1] = 0.0f;                    result.M[3][1] = 0.0f;
		result.M[0][2] = 0.0f;                    result.M[1][2] = 0.0f;                    result.M[2][2] = -2.0f / (far - near); result.M[3][2] = 0.0f;
		result.M[0][3] = -(right + left) / (right - left); result.M[1][3] = -(top + bottom) / (top - bottom); result.M[2][3] = -(far + near) / (far - near); result.M[3][3] = 1.0f;

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

	Matrix Translate(Vector3<T> vector)
	{
		Matrix result = Identity();

		result.M[0][3] = vector.X;
		result.M[1][3] = vector.Y;
		result.M[2][3] = vector.Z;

		return  *this * result;
	}

	Matrix Rotate(T angle)
	{
		Matrix result = Identity();

		float c = cos(angle);
		float s = sin(angle);

		result.M[0][0] = c;
		result.M[0][1] = -s;
		result.M[1][0] = s;
		result.M[1][1] = c;

		return  *this * result;
	}

	Matrix Scale(Vector3<T> vector)
	{
		Matrix result = Identity();

		result.M[0][0] = vector.X;
		result.M[1][1] = vector.Y;
		result.M[2][2] = vector.Z;

		return  *this * result;
	}
};

#endif