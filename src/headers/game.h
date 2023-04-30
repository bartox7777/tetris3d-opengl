#pragma once

#include "shader.h"

#include <glm/glm.hpp>

class Game
{
    glm::mat4 perspective;
    glm::mat4 view;
    unsigned int width;
    unsigned int height;

public:
    Game(unsigned int width, unsigned int height);
    ShaderProgram shaderProgram;
    void initialize();
};