#include "tetracube.h"

Tetracube::Tetracube(ShaderProgram shaderProgram, Camera &camera, Mesh *mesh, TYPE type)
{
    canMove = true;
    switch (type)
    {
    case TYPE::I:
        cubes.push_back(new Cube(shaderProgram, camera, glm::vec3(0.0f, mesh->height - 1, 2.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), mesh));
        cubes.push_back(new Cube(shaderProgram, camera, glm::vec3(0.0f, mesh->height + 1, 2.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), mesh));
        cubes.push_back(new Cube(shaderProgram, camera, glm::vec3(0.0f, mesh->height + 3, 2.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), mesh));
        break;
    }
}

void Tetracube::draw()
{
    for (auto cube : cubes)
    {
        cube->draw();
    }
}

void Tetracube::moveDown(float units)
{
    for (auto cube : cubes)
    {
        cube->moveDown(units);
    }
}

void Tetracube::moveLeft(float units)
{
    for (auto cube : cubes)
    {
        cube->moveLeft(units);
    }
}

void Tetracube::moveRight(float units)
{
    for (auto cube : cubes)
    {
        cube->moveRight(units);
    }
}

void Tetracube::moveForward(float units)
{
    for (auto cube : cubes)
    {
        cube->moveForward(units);
    }
}

void Tetracube::moveBackward(float units)
{
    for (auto cube : cubes)
    {
        cube->moveBackward(units);
    }
}

Tetracube::~Tetracube()
{
    for (auto cube : cubes)
    {
        delete cube;
    }
    cubes.clear();
}

void Tetracube::blockCubesOnBottom() // if one cube can't move, none of them can
{
    for (auto cube1 : cubes)
    {
        if (!cube1->canMove)
        {
            for (auto cube2 : cubes)
            {
                cube2->canMove = false;
            }
            canMove = false;
            break;
        }
    }
}

void Tetracube::setCanMove(bool canMove)
{
    this->canMove = canMove;
    for (auto cube : cubes)
    {
        cube->canMove = canMove;
    }
}

bool Tetracube::getCanMove()
{
    return canMove;
}