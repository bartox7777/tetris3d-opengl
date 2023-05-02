#include "headers/shader.h"
#include "headers/game.h"
#include "headers/cube.h"
#include "headers/camera.h"
#include "headers/mesh.h"
#include "headers/tetracube.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
const std::string TITLE = "Tetris 3D";

void errorCallback(int error, const char *description);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
// void windowResizeCallback(GLFWwindow *window, int width, int height);
void initOpenGLProgram(GLFWwindow *window);
void freeOpenGLProgram(GLFWwindow *window);

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 50.0f);

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    // Set OpenGL version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set OpenGL profile to Core - No Backwards Compatibility

    // Create a window
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, TITLE.c_str(), nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    initOpenGLProgram(window);
    Game Tetris3D(WIDTH, HEIGHT); // here shaders are compiled - is it ok? - be careful with the order of initialization
    Tetris3D.initialize();

    Mesh mesh(Tetris3D.shaderProgram, &camera, 3, 11.5);
    Tetracube tetracube(Tetris3D.shaderProgram, &camera, &mesh, Tetracube::TYPE::I);

    // Cube cube(Tetris3D.shaderProgram, &camera, glm::vec3(0.0f, 10.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), &mesh);
    // Cube cube2(Tetris3D.shaderProgram, &camera, glm::vec3(0.0f, -10.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), &mesh);

    glfwSetTime(0.0);
    float time = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glfwPollEvents(); // process events in the queue and call the callbacks

        // process input

        // update the game
        time += glfwGetTime();

        // render the game
        glfwSetTime(0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mesh.draw();
        tetracube.draw();
        tetracube.blockCubes();

        if (time >= 0.5f)
        {
            // cube.moveDown(2);
            // cube2.moveDown(2);
            tetracube.moveDown(1);
            time = 0.0f;
        }

        // camera.moveVerticalOnCircle(glfwGetTime());
        // std::cout << glm::to_string(camera.position) << " ";
        // std::cout << glm::to_string(camera.upVector) << " ";
        // std::cout << glfwGetTime() << std::endl;
        // camera.moveVerticalOnCircle(0.01f);
        glfwSwapBuffers(window);
    }

    // freeOpenGLProgram(window);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void errorCallback(int error, const char *description)
{
    std::cerr << "Error: " << description << std::endl;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // Close the window if the ESC key was pressed (not released)
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        camera.moveHorizontalOnCircle(10.0f * glfwGetTime());
    }
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        camera.moveHorizontalOnCircle(-10.0f * glfwGetTime());
    }
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        camera.circleRadius -= 0.1f;
        camera.moveHorizontalOnCircle(0.0f);
    }
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        camera.circleRadius += 0.1f;
        camera.moveHorizontalOnCircle(0.0f);
    }
}

void initOpenGLProgram(GLFWwindow *window)
{
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, WIDTH, HEIGHT);

    // Set the error callback
    glfwSetErrorCallback(errorCallback);
    // Set the key callback
    glfwSetKeyCallback(window, keyCallback);
    // Set the window resize callback - resize is problematic
    // glfwSetWindowSizeCallback(window, windowResizeCallback);
}

void freeOpenGLProgram(GLFWwindow *window)
{
}

// void windowResizeCallback(GLFWwindow *window, int width, int height)
// {
//     glViewport(0, 0, width, height);
//     camera.aspect = (float)width / (float)height;
// }