#include "mesh.h"

#include <iostream>

Mesh::Mesh(ShaderProgram shaderProgram, Camera *camera, int width, int height) : shaderProgram(shaderProgram), width(width), height(height), camera(camera)
{
    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    perspective = glm::mat4(1.0f);

    color = {0.0, 0.0, 0.0, 0.2f};

    float vertices[] = {
        0.0f, -1.0f, 0.0f, // bottom point
        0.0f, 1.0f, 0.0f,  // top point
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO
    glBindVertexArray(0);             // unbind VAO
}

void Mesh::draw()
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
    glUniform4fv(shaderProgram.getUniformLocation("ocolor"), 1, glm::value_ptr(color));

    glBindVertexArray(VAO);

    int x = width;
    for (int z = -width; z <= width; z += 2)
    {
        // std::cout << x << " " << z << std::endl;
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1.0f, (float)height, 1.0f));
        model = glm::translate(model, glm::vec3((float)x, 0.0f, (float)z));

        glUniformMatrix4fv(shaderProgram.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_LINES, 0, 2);
    }

    int z = width;
    for (int x = -width; x <= width; x += 2)
    {
        // std::cout << x << " " << z << std::endl;
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1.0f, (float)height, 1.0f));
        model = glm::translate(model, glm::vec3((float)x, 0.0f, (float)z));

        glUniformMatrix4fv(shaderProgram.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_LINES, 0, 2);
    }

    for (int i = -height; i <= height; i += 2)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, (float)i, (float)width));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(1.0f, (float)width, 1.0f));
        glUniformMatrix4fv(shaderProgram.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_LINES, 0, 2);
    }

    for (int i = -height; i <= height; i += 2)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3((float)width, (float)i, 0.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, (float)width, 1.0f));
        glUniformMatrix4fv(shaderProgram.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_LINES, 0, 2);
    }

    for (int i = -width; i <= width; i += 2)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, (float)-height, (float)i));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(1.0f, (float)width, 1.0f));
        glUniformMatrix4fv(shaderProgram.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_LINES, 0, 2);
    }

    for (int i = -width; i <= width; i += 2)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3((float)i, (float)-height, 0.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, (float)width, 1.0f));
        glUniformMatrix4fv(shaderProgram.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_LINES, 0, 2);
    }

    glBindVertexArray(0);
}

int Mesh::getMinY()
{
    return -height;
}

int Mesh::getMaxX()
{
    return width;
}

int Mesh::getMinX()
{
    return -width;
}

int Mesh::getMaxZ()
{
    return width;
}

int Mesh::getMinZ()
{
    return -width;
}