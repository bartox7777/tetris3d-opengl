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

            // check if tetracube can move down - is other tetracube below
            // create function to it
            for (auto otherTetracube : tetracubes)
            {
                if (tetracube != otherTetracube)
                {
                    for (auto cube : tetracube->cubes)
                    {
                        for (auto otherCube : otherTetracube->cubes)
                        {
                            if (cube->position - glm::vec3(0.0f, 2.0f, 0.0f) == otherCube->position)
                            {
                                tetracube->setCanMove(false);
                            }
                        }
                    }
                }
            }
            tetracube->moveDown(2);
        }
    }

    if (tetracubes[0]->getCanMove() == false)
    {
        // active tetracube insert at beginning of tetracubes
        tetracubes.insert(tetracubes.begin(), new Tetracube(*shaderProgram, camera, mesh, Tetracube::TYPE::I));
    }
}

void Game::processInput(int key)
{
    bool moveCanBeMade = true;
    if (tetracubes.size() > 0)
    {
        switch (key)
        {
        case GLFW_KEY_LEFT:
            for (auto otherTetracube : tetracubes)
            {
                if (tetracubes[0] != otherTetracube)
                {
                    for (auto cube : tetracubes[0]->cubes)
                    {
                        for (auto otherCube : otherTetracube->cubes)
                        {
                            if (cube->position + glm::vec3(2.0f, 0.0f, 0.0f) == otherCube->position)
                            {
                                moveCanBeMade = false;
                            }
                        }
                    }
                }
            }
            if (moveCanBeMade)
            {
                tetracubes[0]->moveLeft(2);
            }
            break;
        case GLFW_KEY_RIGHT:
            for (auto otherTetracube : tetracubes)
            {
                if (tetracubes[0] != otherTetracube)
                {
                    for (auto cube : tetracubes[0]->cubes)
                    {
                        for (auto otherCube : otherTetracube->cubes)
                        {
                            if (cube->position - glm::vec3(2.0f, 0.0f, 0.0f) == otherCube->position)
                            {
                                moveCanBeMade = false;
                            }
                        }
                    }
                }
            }
            if (moveCanBeMade)
            {
                tetracubes[0]->moveRight(2);
            }
            break;
        case GLFW_KEY_DOWN:
            for (auto otherTetracube : tetracubes)
            {
                if (tetracubes[0] != otherTetracube)
                {
                    for (auto cube : tetracubes[0]->cubes)
                    {
                        for (auto otherCube : otherTetracube->cubes)
                        {
                            if (cube->position - glm::vec3(0.0f, 0.0f, 2.0f) == otherCube->position)
                            {
                                moveCanBeMade = false;
                            }
                        }
                    }
                }
            }
            if (moveCanBeMade)
            {
                tetracubes[0]->moveBackward(2);
            }
            break;
        case GLFW_KEY_UP:
            for (auto otherTetracube : tetracubes)
            {
                if (tetracubes[0] != otherTetracube)
                {
                    for (auto cube : tetracubes[0]->cubes)
                    {
                        for (auto otherCube : otherTetracube->cubes)
                        {
                            if (cube->position + glm::vec3(0.0f, 0.0f, 2.0f) == otherCube->position)
                            {
                                moveCanBeMade = false;
                            }
                        }
                    }
                }
            }
            if (moveCanBeMade)
            {
                tetracubes[0]->moveForward(2);
            }
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