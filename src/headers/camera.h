#pragma once

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 50.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
class Camera
{
public:
    // Camera(glm::vec3 position, glm::vec3 lookingAtPoint, glm::vec3 upVector, float FOV, float aspect, float nearPlane, float farPlane);
    // glm::vec3 position;
    // glm::vec3 lookingAtPoint;
    // glm::vec3 upVector;
    float fov;
    float aspect;
    float nearPlane;
    float farPlane;
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    // float angleHorizontal;
    // float angleVertical;
    // float circleRadius;

    // void moveHorizontalOnCircle(float distance);
    // void moveVerticalOnCircle(float distance);
    // void handleMoveRight();
    // void handleMoveLeft();
    // void handleMoveForward();
    // void handleMoveBackward();

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float fov = 45.0f, float aspectRatio = 1.0f, float yaw = YAW, float pitch = PITCH, float nearPlane = 0.1f, float farPlane = 50.0f);
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

private:
    void updateCameraVectors();
};