#pragma once

#include "shader.h"
#include "camera.h"
#include "mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Base
{
    ShaderProgram shaderProgram;
    unsigned int VBO, VAO, EBO;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 perspective;
    Camera *camera;
    glm::vec4 color;
    Mesh *mesh;
    // unsigned verticesCount = 132;
    unsigned verticesCount = 180;

public:
    unsigned int texture;
    glm::vec3 position;

    Base(ShaderProgram shaderProgram, Camera *camera, Mesh *mesh);
    void draw();
};