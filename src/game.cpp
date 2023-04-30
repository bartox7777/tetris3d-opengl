#include "game.h"
#include "shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Game::Game(unsigned int width, unsigned int height) : shaderProgram("./src/shaders/vertexShader.glsl", "./src/shaders/fragmentShader.glsl")
{
    // this->width = width;
    // this->height = height;
    // this->view = glm::lookAt(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f),
    //                          glm::vec3(0.0f, 1.0f, 0.0f));
    // this->perspective = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
}

void Game::initialize()
{
    // shaderProgram.use();
    // glUniformMatrix4fv(shaderProgram.getUniformLocation("perspective"), 1, GL_FALSE, glm::value_ptr(perspective));
    // glUniformMatrix4fv(shaderProgram.getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
}
