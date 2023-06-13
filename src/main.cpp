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
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void processOffset(double xpos, double ypos);
// void windowResizeCallback(GLFWwindow *window, int width, int height);
void initOpenGLProgram(GLFWwindow *window);
void freeOpenGLProgram(GLFWwindow *window);


Camera camera(glm::vec3(-10.0f, 21.0f, -11.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, (float)WIDTH / (float)HEIGHT, 49.0f, -52.0f, 0.1f, 50.0f);
Game Tetris3D(camera);

int main()
{
    // Initialize GLFW
    glfwSetErrorCallback(errorCallback);
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

    Tetris3D.initialize();

    // Cube cube(*Tetris3D.shaderProgram, &camera, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), Tetris3D.mesh);

    glfwSetTime(0.0);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
        glfwPollEvents(); // process events in the queue and call the callbacks

        // process input

        // update the game
        Tetris3D.update(glfwGetTime());

        // render the game
        glfwSetTime(0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Tetris3D.draw();
        // cube.draw();

        // Move forward
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(Camera_Movement::FORWARD, glfwGetTime());
        }
        // Move backward
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(Camera_Movement::BACKWARD, glfwGetTime());
        }
        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(Camera_Movement::RIGHT, glfwGetTime());
        }
        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            camera.ProcessKeyboard(Camera_Movement::LEFT, glfwGetTime());
        }

        std::cout << "Camera lookat: " << glm::to_string(camera.Front+camera.Position) << std::endl;
        std::cout << "Camera position: " << glm::to_string(camera.Position) << std::endl;
        std::cout << "Camera Front: " << glm::to_string(camera.Front) << std::endl;
        std::cout << "Camera Yaw: " << camera.Yaw << std::endl;
        std::cout << "Camera Pitch: " << camera.Pitch << std::endl;

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
    // if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
    // {
    //     camera.processkeyboard(Camera::Movement::RIGHT, glfwGetTime());
    // }
    // if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
    // {
    //     camera.handleMoveLeft();
    // }
    // if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
    // {
    //     camera.handleMoveForward();
    // }
    // if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
    // {
    //     camera.handleMoveBackward();
    // }
    if (action == GLFW_PRESS)
    {
        Tetris3D.processInput(key);
    }
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    static bool firstMouse = true;
    float lastX = 400, lastY = 300;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    processOffset(xpos, ypos);
}

void processOffset(double xpos, double ypos)
{
    static double lastX = xpos;
    static double lastY = ypos;

    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
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
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // Set the window resize callback - resize is problematic
    // glfwSetWindowSizeCallback(window, windowResizeCallback);
}

// void freeOpenGLProgram(GLFWwindow *window)
// {
// }

// void windowResizeCallback(GLFWwindow *window, int width, int height)
// {
//     glViewport(0, 0, width, height);
//     camera.aspect = (float)width / (float)height;
// }