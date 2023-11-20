#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "glad.h"
#include <vector2.h>
#include <vector3.h>
#include <matrix.h>
#include <array>

class Shader
{
public:
	unsigned int ID;

	Shader(const std::string& vertexCode, const std::string& fragmentCode);
	void Use();
	void SetFloat(const std::string& name, float value);
	void SetInteger(const std::string& name, int value);
	void SetVector2f(const std::string& name, float x, float y);
	void SetVector2f(const std::string& name, const Vector2<float>& value);
	void SetVector3f(const std::string& name, float x, float y, float z);
	void SetVector3f(const std::string& name, const Vector3<float>& value);
	void SetMatrix4(const std::string& name, const Matrix<float>& matrix);

private:
	void checkCompilerErrors(GLuint shader, std::string type);
	std::array<GLfloat, 16> TranslateMatrix(Matrix<float> matrix);
};

#endif