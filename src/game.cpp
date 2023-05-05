#include "game.h"
#include "shader.h"
#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Game::Game(Camera *camera) : shaderProgram(nullptr), camera(camera), mesh(nullptr), time(0.0f)
{
}

// compile shaders
void Game::initialize()
{
    shaderProgram = new ShaderProgram("./src/shaders/vertexShader.glsl", "./src/shaders/fragmentShader.glsl");
    mesh = new Mesh(*shaderProgram, camera, 3, 12);
    tetracubes.push_back(new Tetracube(*shaderProgram, camera, mesh, Tetracube::TYPE::I));
}

void Game::draw()
{
    mesh->draw();
    for (auto tetracube : tetracubes)
    {
        tetracube->draw();
    }
}

void Game::update(float dt)
{
    for (auto tetracube : tetracubes)
    {
        tetracube->blockCubesOnBottom();
    }

    time += dt;
    if (time >= 1.0f)
    {
        time = 0.0f;
        for (auto tetracube : tetracubes)
        {
            tetracube->moveDown(2);
        }
    }
}

void Game::processInput(int key)
{
    if (tetracubes.size() > 0)
    {
        switch (key)
        {
        case GLFW_KEY_LEFT:
            tetracubes[0]->moveLeft(2);
            break;
        case GLFW_KEY_RIGHT:
            tetracubes[0]->moveRight(2);
            break;
        case GLFW_KEY_DOWN:
            tetracubes[0]->moveBackward(2);
            break;
        case GLFW_KEY_UP:
            tetracubes[0]->moveForward(2);
            break;
        }
    }
}

Game::~Game()
{
    delete shaderProgram;
    delete mesh;
    for (auto tetracube : tetracubes)
    {
        delete tetracube;
    }
    tetracubes.clear();
}