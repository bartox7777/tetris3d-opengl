#pragma once

#include <vector>
#include "cube.h"

class Tetracube // unnecessary tetra- prefix, but I can't think of a better name
{
    bool canMove;

public:
    enum TYPE
    {
        I,
        i,
        O,
        o,
        T,
        L,
        l
    };
    std::vector<Cube *> cubes;
    void setCanMove(bool canMove);
    bool getCanMove();
    Tetracube(ShaderProgram shaderProgram, Camera *camera, Mesh *mesh, TYPE type);
    void draw();
    void moveDown(float units);
    void moveLeft(float units);
    void moveRight(float units);
    void moveForward(float units);
    void moveBackward(float units);
    void blockCubesOnBottom();
    ~Tetracube();
};