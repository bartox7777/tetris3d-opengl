#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera(glm::vec3 position, glm::vec3 lookingAtPoint, glm::vec3 upVector, float FOV, float aspect, float nearPlane, float farPlane);
    glm::vec3 position;
    glm::vec3 lookingAtPoint;
    glm::vec3 upVector;
    float FOV;
    float aspect;
    float nearPlane;
    float farPlane;
    float angleHorizontal;
    float angleVertical;
    float circleRadius;

    void moveHorizontalOnCircle(float distance);
    void moveVerticalOnCircle(float distance);
};