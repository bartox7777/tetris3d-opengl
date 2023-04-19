#pragma once

#include "shader.h"

#include <glm/glm.hpp>

class Game
{
public:
    unsigned int width;
    unsigned int height;
    ShaderProgram shaderProgram;
    glm::mat4 perspective;
    glm::mat4 view;

    Game(unsigned int width, unsigned int height);
    void initialize();
};