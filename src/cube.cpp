#include "cube.h"

Cube::Cube(ShaderProgram shaderProgram, Camera *camera, glm::vec3 position) : shaderProgram(shaderProgram), position(position)
{
    this->camera = camera;

    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    perspective = glm::mat4(1.0f);

    float vertices[] = {
        // 3d cube
        1.0f, 1.0f, 1.0f,    // front right top
        1.0f, -1.0f, 1.0f,   // front right bottom
        -1.0f, -1.0f, 1.0f,  // front left bottom
        -1.0f, 1.0f, 1.0f,   // front left top
        1.0f, 1.0f, -1.0f,   // back right top
        1.0f, -1.0f, -1.0f,  // back right bottom
        -1.0f, -1.0f, -1.0f, // back left bottom
        -1.0f, 1.0f, -1.0f   // back left top
    };
    unsigned int indices[] = {
        // front
        0, 1, 3,
        1, 2, 3,
        // right
        0, 4, 1,
        1, 4, 5,
        // back
        4, 7, 5,
        5, 7, 6,
        // left
        7, 3, 6,
        6, 3, 2,
        // top
        7, 4, 0,
        7, 0, 3,
        // bottom
        1, 5, 2,
        2, 5, 6};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);         // unbind VBO
    glBindVertexArray(0);                     // unbind VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind EBO
}

void Cube::Draw()
{
    shaderProgram.use();
    model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(
        camera->position,
        camera->lookingAtPoint,
        camera->upVector); // Wylicz macierz widoku

    glm::mat4 projection = glm::perspective(camera->FOV, camera->aspect, camera->nearPlane, camera->farPlane); // Wylicz macierz rzutowania
    glUniformMatrix4fv(shaderProgram.getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shaderProgram.getUniformLocation("perspective"), 1, GL_FALSE, glm::value_ptr(projection));

    // model = glm::translate(model, position);
    // model = glm::rotate(model, glm::radians(35.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glUniformMatrix4fv(shaderProgram.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}