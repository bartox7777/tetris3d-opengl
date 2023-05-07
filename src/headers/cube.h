#pragma once

#include <iostream>

#include "shader.h"
#include "camera.h"
#include "mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Cube
{

    ShaderProgram shaderProgram;
    unsigned int VBO, VAO, EBO;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 perspective;
    Camera *camera;
    glm::vec3 color;
    Mesh *mesh;

public:
    unsigned int texture;
    Cube(ShaderProgram shaderProgram, Camera *camera, glm::vec3 position, glm::vec4 color, Mesh *mesh);
    void draw();
    void moveDown(float units);
    void moveLeft(float units);
    void moveRight(float units);
    void moveForward(float units);
    void moveBackward(float units);
    bool canMove = true;
    glm::vec3 position;
};