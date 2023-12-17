#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <spdlog/spdlog.h>

Shader::Shader(const std::string& vertexCode, const std::string& fragmentCode):
    logger(nullptr)
{
    logger = spdlog::get("karakuri_logger");

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompilerErrors(vertex, "Vertex");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompilerErrors(fragment, "Fragment");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompilerErrors(ID, "Program");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use()
{
    glUseProgram(ID);
}

void Shader::checkCompilerErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];

    if (type != "Program")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            logger->error("Compliation error type of {} with info {}", type, infoLog);
        }
    }
    else
    {
        glGetShaderiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            logger->error("Program linking error type of {} with info {}", type, infoLog);
        }
    }
}

void Shader::SetFloat(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::SetInteger(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::SetVector2f(const std::string& name, float x, float y) {
    glUniform2f(glGetUniformLocation(this->ID, name.c_str()), x, y);
}

void Shader::SetVector2f(const std::string& name, Vector2<float> value) {
    glUniform2f(glGetUniformLocation(this->ID, name.c_str()), value.X, value.Y);
}

void Shader::SetVector3f(const std::string& name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(this->ID, name.c_str()), x, y, z);
}

void Shader::SetVector3f(const std::string& name, Vector3<float> value) {
    glUniform3f(glGetUniformLocation(this->ID, name.c_str()), value.X, value.Y, value.Z);
}

void Shader::SetMatrix4(const std::string& name, Matrix<float> matrix) 
{
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, false, TranslateMatrix(matrix).data());
}

std::array<GLfloat, 16> Shader::TranslateMatrix(Matrix<float> matrix)
{
    std::array<GLfloat, 16> MArray;

    int index = 0;
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            MArray[index++] = matrix.M[row][col];
        }
    }

    return MArray;
}

void Shader::Destroy()
{
    logger.reset();
}