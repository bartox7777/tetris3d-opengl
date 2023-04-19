#include "headers/shader.h"

#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram(std::string vertexPath, std::string fragmentPath)
{
    std::string vertexShaderSource = readFile(vertexPath);
    std::string fragmentShaderSource = readFile(fragmentPath);

    const char *vertexShaderSourceC = vertexShaderSource.c_str();
    const char *fragmentShaderSourceC = fragmentShaderSource.c_str();

    this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);                // Create a vertex shader
    glShaderSource(this->vertexShaderID, 1, &vertexShaderSourceC, nullptr); // Attach the source code to the shader
    glCompileShader(this->vertexShaderID);                                  // Compile the shader
    checkCompileErrors(this->vertexShaderID, ObjectType::VERTEX);           // Check for errors

    // same as above but for fragment shader
    this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->fragmentShaderID, 1, &fragmentShaderSourceC, nullptr);
    glCompileShader(this->fragmentShaderID);
    checkCompileErrors(this->fragmentShaderID, ObjectType::FRAGMENT);

    this->shaderProgramID = glCreateProgram(); // Create a shader program - a collection of compiled shaders
    glAttachShader(this->shaderProgramID, this->vertexShaderID);
    glAttachShader(this->shaderProgramID, this->fragmentShaderID);
    glLinkProgram(this->shaderProgramID); // Link compiled shaders in order to create a shader program
    checkCompileErrors(this->shaderProgramID, ObjectType::PROGRAM);

    glDeleteShader(this->vertexShaderID); // We don't need the shaders anymore - they are already compiled and linked
    glDeleteShader(this->fragmentShaderID);
}

void ShaderProgram::use()
{
    glUseProgram(shaderProgramID);
}

GLuint ShaderProgram::getUniformLocation(std::string uniformName)
{
    return glGetUniformLocation(this->shaderProgramID, uniformName.c_str());
}

// GLuint ShaderProgram::getAttributeLocation(std::string attributeName)
// {
//     return glGetAttribLocation(this->shaderProgramID, attributeName.c_str());
// }

void ShaderProgram::checkCompileErrors(GLuint object, ObjectType type)
{
    GLint success;
    GLchar infoLog[1024];
    switch (type)
    {
    case ObjectType::PROGRAM:
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED " << infoLog << std::endl;
        }
        break;
    case ObjectType::VERTEX:
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED " << infoLog << std::endl;
        }
        break;
    case ObjectType::FRAGMENT:
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED " << infoLog << std::endl;
        }
        break;
    }
}

std::string ShaderProgram::readFile(std::string filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()); // Read the file into a string
    file.close();
    return content;
}
