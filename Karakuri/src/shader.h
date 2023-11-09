#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include "../include/glm/glm.hpp"

class Shader
{
public:
	unsigned int ID;

	Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	void Use();
	void SetFloat(const std::string& name, float value);
	void SetInteger(const std::string& name, int value);
	void SetVector2f(const std::string& name, float x, float y);
	void SetVector2f(const std::string& name, const glm::vec2& value);
	void SetVector3f(const std::string& name, float x, float y, float z);
	void SetVector3f(const std::string& name, const glm::vec3& value);
	void SetVector4f(const std::string& name, float x, float y, float z, float w);
	void SetVector4f(const std::string& name, const glm::vec4& value);
	void SetMatrix4(const std::string& name, const glm::mat4& matrix);

private:
	void checkCompilerErrors(GLuint shader, std::string type);
};

#endif