#pragma once

#include <string>

#include <GL/glew.h>

class ShaderProgram
{
private:
    GLuint shaderProgramID;
    GLuint vertexShaderID;
    GLuint fragmentShaderID;

    enum class ObjectType
    {
        VERTEX,
        FRAGMENT,
        PROGRAM
    };
    void checkCompileErrors(GLuint shader, ObjectType type);

public:
    ShaderProgram(std::string vertexPath, std::string fragmentPath); // Read and compile shaders from files and create a shader program
    static std::string readFile(std::string filePath);
    void use();
};