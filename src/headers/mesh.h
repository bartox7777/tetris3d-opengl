#pragma once

#include "shader.h"
#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Mesh
{
    int width, height;
    ShaderProgram shaderProgram;
    unsigned int VBO, VAO, EBO;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 perspective;
    Camera *camera;
    glm::vec4 color;

public:
    glm::vec3 position;

    Mesh(ShaderProgram shaderProgram, Camera *camera, int width, int height);
    void Draw();
};