#include "camera.h"

#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 lookingAtPoint, glm::vec3 upVector, float FOV, float aspect, float nearPlane, float farPlane)
{
    this->position = position;
    this->lookingAtPoint = lookingAtPoint;
    this->upVector = upVector;
    this->FOV = FOV;
    this->aspect = aspect;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;

    this->angleHorizontal = 0.0f;
    this->angleVertical = 0.0f;
    this->circleRadius = 10.0f;

    moveHorizontalOnCircle(this->angleHorizontal);
    // moveVerticalOnCircle(this->angleVertical);
}

// its not working as it should - very provisional implementation
void Camera::moveHorizontalOnCircle(float angle)
{
    glm::vec3 newPosition = position;
    // // std::cout << newPosition.x + sin(angle) << " " << newPosition.z + cos(angle) << std::endl;
    this->angleHorizontal += angle;
    newPosition.x = glm::sin(this->angleHorizontal);
    newPosition.z = glm::cos(this->angleHorizontal);

    position.x = newPosition.x * circleRadius;
    position.z = newPosition.z * circleRadius;
    // position.x = glm::normalize(position).x * circleRadius;
    // position.z = glm::normalize(position).z * circleRadius;
}

// void Camera::moveVerticalOnCircle(float angle)
// {
//     this->angleVertical += angle;
//     position.y = this->angleVertical;
//     position.y = glm::normalize(position).y * circleRadius;
// }