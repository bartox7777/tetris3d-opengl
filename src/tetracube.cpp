#include "tetracube.h"

Tetracube::Tetracube(ShaderProgram shaderProgram, Camera *camera, Mesh *mesh, TYPE type)
{
    switch (type)
    {
    case TYPE::I:
        cubes.push_back(new Cube(shaderProgram, camera, glm::vec3(0.0f, mesh->height, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), mesh));
        cubes.push_back(new Cube(shaderProgram, camera, glm::vec3(0.0f, mesh->height + 2, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), mesh));
        cubes.push_back(new Cube(shaderProgram, camera, glm::vec3(0.0f, mesh->height + 4, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), mesh));
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

Tetracube::~Tetracube()
{
    for (auto cube : cubes)
    {
        delete cube;
    }
    cubes.clear();
}

void Tetracube::blockCubes() // if one cube can't move, none of them can
{
    for (auto cube1 : cubes)
    {
        if (!cube1->canMove)
        {
            for (auto cube2 : cubes)
            {
                cube2->canMove = false;
            }
        }
    }
}