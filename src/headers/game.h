#pragma once

#include "shader.h"
#include "tetracube.h"
#include "mesh.h"

#include <glm/glm.hpp>
#include <vector>

class Game
{
    // glm::mat4 perspective;
    // glm::mat4 view;
    // unsigned int width;
    // unsigned int height;
    enum class GameState
    {
        ACTIVE,
        LOSS
    };
    std::vector<Tetracube *> tetracubes;
    
    float time;

public:
    Mesh *mesh;
    Game(Camera *camera);
    ShaderProgram *shaderProgram;
    Camera *camera;
    void initialize();
    void draw();
    void update(float dt);
    void processInput(int key);
    ~Game();
};