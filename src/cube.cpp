#include "cube.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Cube::Cube(ShaderProgram shaderProgram, Camera *camera, glm::vec3 position, glm::vec4 color, Mesh *mesh) : shaderProgram(shaderProgram), position(position), camera(camera), color(color), mesh(mesh)
{
    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    perspective = glm::mat4(1.0f);

    // float vertices[] = {
    //     // 3d cube
    //     1.0f, 1.0f, 1.0f, color.x, color.y, color.z, color.w, 1.0f, 1.0f,    // front right top
    //     1.0f, -1.0f, 1.0f, color.x, color.y, color.z, color.w, 1.0f, 0.0f,   // front right bottom
    //     -1.0f, -1.0f, 1.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f,  // front left bottom
    //     -1.0f, 1.0f, 1.0f, color.x, color.y, color.z, color.w, 0.0f, 1.0f,   // front left top
    //     1.0f, 1.0f, -1.0f, color.x, color.y, color.z, color.w, 0.0f, 1.0f,   // back right top
    //     1.0f, -1.0f, -1.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f,  // back right bottom
    //     -1.0f, -1.0f, -1.0f, color.x, color.y, color.z, color.w, 1.0f, 0.0f, // back left bottom
    //     -1.0f, 1.0f, -1.0f, color.x, color.y, color.z, color.w, 1.0f, 1.0f,  // back left top

    //     1.0f, 1.0f, 1.0f, color.x, color.y, color.z, color.w, 1.0f, 1.0f, // front right top

    //     1.0f, -1.0f, 1.0f, color.x, color.y, color.z, color.w, 1.0f, 1.0f,  // front right bottom
    //     -1.0f, -1.0f, 1.0f, color.x, color.y, color.z, color.w, 0.0f, 1.0f, // front left bottom

    //     -1.0f, 1.0f, 1.0f, color.x, color.y, color.z, color.w, 0.0f, 1.0f, // front left top
    //     1.0f, 1.0f, -1.0f, color.x, color.y, color.z, color.w, 1.0f, 0.0f, // back right top

    //     1.0f, -1.0f, -1.0f, color.x, color.y, color.z, color.w, 1.0f, 0.0f,  // back right bottom
    //     -1.0f, -1.0f, -1.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f, // back left bottom

    //     -1.0f, 1.0f, -1.0f, color.x, color.y, color.z, color.w, 0.0f, 0.0f, // back left top
    // };

    float vertices[]={
				1.0f,-1.0f,-1.0f,1.0f,
				-1.0f, 1.0f,-1.0f,1.0f,
				-1.0f,-1.0f,-1.0f,1.0f,

				1.0f,-1.0f,-1.0f,1.0f,
				1.0f, 1.0f,-1.0f,1.0f,
				-1.0f, 1.0f,-1.0f,1.0f,


				-1.0f,-1.0f, 1.0f,1.0f,
				1.0f, 1.0f, 1.0f,1.0f,
				1.0f,-1.0f, 1.0f,1.0f,

				-1.0f,-1.0f, 1.0f,1.0f,
				-1.0f, 1.0f, 1.0f,1.0f,
				1.0f, 1.0f, 1.0f,1.0f,

				1.0f,-1.0f, 1.0f,1.0f,
				1.0f, 1.0f,-1.0f,1.0f,
				1.0f,-1.0f,-1.0f,1.0f,

				1.0f,-1.0f, 1.0f,1.0f,
				1.0f, 1.0f, 1.0f,1.0f,
				1.0f, 1.0f,-1.0f,1.0f,

				-1.0f,-1.0f,-1.0f,1.0f,
				-1.0f, 1.0f, 1.0f,1.0f,
				-1.0f,-1.0f, 1.0f,1.0f,

				-1.0f,-1.0f,-1.0f,1.0f,
				-1.0f, 1.0f,-1.0f,1.0f,
				-1.0f, 1.0f, 1.0f,1.0f,

				-1.0f,-1.0f,-1.0f,1.0f,
				1.0f,-1.0f, 1.0f,1.0f,
				1.0f,-1.0f,-1.0f,1.0f,

				-1.0f,-1.0f,-1.0f,1.0f,
				-1.0f,-1.0f, 1.0f,1.0f,
				1.0f,-1.0f, 1.0f,1.0f,

				-1.0f, 1.0f, 1.0f,1.0f,
				1.0f, 1.0f,-1.0f,1.0f,
				1.0f, 1.0f, 1.0f,1.0f,

				-1.0f, 1.0f, 1.0f,1.0f,
				-1.0f, 1.0f,-1.0f,1.0f,
				1.0f, 1.0f,-1.0f,1.0f,

			};

    float vertexNormals[]={
				1.0f,-1.0f,-1.0f,0.0f,
				-1.0f, 1.0f,-1.0f,0.0f,
				-1.0f,-1.0f,-1.0f,0.0f,

				1.0f,-1.0f,-1.0f,0.0f,
				1.0f, 1.0f,-1.0f,0.0f,
				-1.0f, 1.0f,-1.0f,0.0f,


				-1.0f,-1.0f, 1.0f,0.0f,
				1.0f, 1.0f, 1.0f,0.0f,
				1.0f,-1.0f, 1.0f,0.0f,

				-1.0f,-1.0f, 1.0f,0.0f,
				-1.0f, 1.0f, 1.0f,0.0f,
				1.0f, 1.0f, 1.0f,0.0f,

				1.0f,-1.0f, 1.0f,0.0f,
				1.0f, 1.0f,-1.0f,0.0f,
				1.0f,-1.0f,-1.0f,0.0f,

				1.0f,-1.0f, 1.0f,0.0f,
				1.0f, 1.0f, 1.0f,0.0f,
				1.0f, 1.0f,-1.0f,0.0f,

				-1.0f,-1.0f,-1.0f,0.0f,
				-1.0f, 1.0f, 1.0f,0.0f,
				-1.0f,-1.0f, 1.0f,0.0f,

				-1.0f,-1.0f,-1.0f,0.0f,
				-1.0f, 1.0f,-1.0f,0.0f,
				-1.0f, 1.0f, 1.0f,0.0f,

				-1.0f,-1.0f,-1.0f,0.0f,
				1.0f,-1.0f, 1.0f,0.0f,
				1.0f,-1.0f,-1.0f,0.0f,

				-1.0f,-1.0f,-1.0f,0.0f,
				-1.0f,-1.0f, 1.0f,0.0f,
				1.0f,-1.0f, 1.0f,0.0f,

				-1.0f, 1.0f, 1.0f,0.0f,
				1.0f, 1.0f,-1.0f,0.0f,
				1.0f, 1.0f, 1.0f,0.0f,

				-1.0f, 1.0f, 1.0f,0.0f,
				-1.0f, 1.0f,-1.0f,0.0f,
				1.0f, 1.0f,-1.0f,0.0f,
			};

    float texCoords[]={
        1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
        1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

        1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
        1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

        1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
        1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

        1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
        1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

        1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
        1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

        1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
        1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
    };

    float combined[36*(4+4+3)];
    int k = 0;
    for (int i=0; i<36; i++){
        for (int j=0; j<4; j++){
            combined[k++]=vertices[i*4+j];
        }
        for (int j=0; j<4; j++){
            combined[k++] = vertexNormals[i*4+j];
        }
        for (int j=0; j<2; j++){
            combined[k++] = texCoords[i*2+j];
        }

    }

    // unsigned int indices[] = {
    //     // front
    //     0, 1, 3,
    //     1, 2, 3,
    //     // right
    //     0, 4, 1,
    //     1, 4, 5,
    //     // back
    //     4, 7, 5,
    //     5, 7, 6,
    //     // left
    //     7, 3, 6,
    //     6, 3, 2,
    //     // top
    //     7 + 8, 4 + 8, 0 + 8,
    //     7 + 8, 0 + 8, 3 + 8,
    //     // bottom
    //     1 + 8, 5 + 8, 2 + 8,
    //     2 + 8, 5 + 8, 6 + 8};
    unsigned int indices[36];
    for (int i=0; i<36; i++){
        indices[i]=i;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(combined), combined, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void *)(4 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void *)(8 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE0);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    shaderProgram.use();
    glUniform1i(shaderProgram.getUniformLocation("texture1"), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);         // unbind VBO
    glBindVertexArray(0);                     // unbind VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind EBO
}

void Cube::draw()
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

    model = glm::translate(model, position);
    // model = glm::rotate(model, glm::radians(35.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glUniformMatrix4fv(shaderProgram.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Cube::moveDown(float units)
{
    if (canMove)
    {
        position.y -= units;
        if (position.y <= (mesh->getMinY() + 1.0f)) // +1.0f bo długość boku kostki to 2.0f, a środek kostki jest środkiem układu współrzędnych modelu
        {
            position.y = (mesh->getMinY() + 1.0f);
            canMove = false;
        }
    }
}

void Cube::moveLeft(float units)
{
    if (canMove)
    {

        position.x += units;
        if (position.x >= (mesh->getMaxX() - 1.0f))
        {
            position.x = (mesh->getMaxX() - 1.0f);
        }
    }
}

void Cube::moveRight(float units)
{
    if (canMove)
    {
        position.x -= units;
        if (position.x <= (mesh->getMinX() + 1.0f))
        {
            position.x = (mesh->getMinX() + 1.0f);
        }
    }
}

void Cube::moveForward(float units)
{
    if (canMove)
    {
        position.z += units;
        if (position.z >= (mesh->getMaxZ() - 1.0f))
        {
            position.z = (mesh->getMaxZ() - 1.0f);
        }
    }
}

void Cube::moveBackward(float units)
{
    if (canMove)
    {
        position.z -= units;
        if (position.z <= (mesh->getMinZ() + 1.0f))
        {
            position.z = (mesh->getMinZ() + 1.0f);
        }
    }
}