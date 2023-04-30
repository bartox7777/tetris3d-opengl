#pragma once

#include <iostream>

#include "shader.h"
#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Cube
{

    ShaderProgram shaderProgram;
    glm::vec3 position;
    unsigned int VBO, VAO, EBO;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 perspective;
    Camera *camera;

public:
    Cube(ShaderProgram shaderProgram, Camera *camera, glm::vec3 position);
    void Draw();
};