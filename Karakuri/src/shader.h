#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>

class Shader
{
public:
	unsigned int ID;

	Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	void use();

private:
	void checkCompilerErrors(GLuint shader, std::string type);
};

#endif