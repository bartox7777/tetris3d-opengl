#include "base.h"

#include <iostream>

// #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Base::Base(ShaderProgram shaderProgram, Camera *camera, Mesh *mesh) : shaderProgram(shaderProgram), camera(camera), mesh(mesh)
{
    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    perspective = glm::mat4(1.0f);

    position = glm::vec3(0.0f, mesh->getMinY() - 1.0f, 0.0f);
    color = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f); // make it brighter

    // float combined[] = {-2.427788, -0.29933, -2.616842, 1.0, -1.0, -0.0, -0.0, 1.0, 0.625, 0.0, -2.427788, 0.101693, 2.616842, 1.0, -1.0, -0.0, -0.0, 1.0, 0.375, 0.25, -2.427788, 0.101693, -2.616842, 1.0, -1.0, -0.0, -0.0, 1.0, 0.375, 0.0, -2.427788, -0.29933, 2.616842, 1.0, -0.0, -0.0, 1.0, 1.0, 0.625, 0.25, 2.427788, 0.101693, 2.616842, 1.0, -0.0, -0.0, 1.0, 1.0, 0.375, 0.5, -2.427788, 0.101693, 2.616842, 1.0, -0.0, -0.0, 1.0, 1.0, 0.375, 0.25, 2.427788, -0.29933, 2.616842, 1.0, 1.0, -0.0, -0.0, 1.0, 0.625, 0.5, 2.427788, 0.101693, -2.616842, 1.0, 1.0, -0.0, -0.0, 1.0, 0.375, 0.75, 2.427788, 0.101693, 2.616842, 1.0, 1.0, -0.0, -0.0, 1.0, 0.375, 0.5, 2.427788, -0.29933, -2.616842, 1.0, -0.0, -0.0, -1.0, 1.0, 0.625, 0.75, -2.427788, 0.101693, -2.616842, 1.0, -0.0, -0.0, -1.0, 1.0, 0.375, 1.0, 2.427788, 0.101693, -2.616842, 1.0, -0.0, -0.0, -1.0, 1.0, 0.375, 0.75, 2.226569, 0.101693, -2.415624, 1.0, -1.0, -0.0, -0.0, 1.0, 0.36464, 0.740388, 2.226569, -0.107441, 2.415624, 1.0, -1.0, -0.0, -0.0, 1.0, 0.36464, 0.509612, 2.226569, 0.101693, 2.415624, 1.0, -1.0, -0.0, -0.0, 1.0, 0.36464, 0.509612, -2.427788, -0.29933, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.875, 0.5, 2.427788, -0.29933, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.625, 0.75, 2.427788, -0.29933, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.625, 0.5, -2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.5, -2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.75, -2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.5, 2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.5, -2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.5, 2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.5, 2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.75, 2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.5, 2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.75, -2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.75, 2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.75, -2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.75, -2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.5, -2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.75, -2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.5, 2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.5, -2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.5, 2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.5, 2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.75, 2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.5, 2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.75, -2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.75, 2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.75, -2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.75, -2.226569, 0.101693, -2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.13536, 0.740388, -2.427788, 0.101693, 2.616842, 1.0, -0.0, 1.0, -0.0, 1.0, 0.125, 0.5, -2.226569, 0.101693, 2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.13536, 0.509612, -2.226569, 0.101693, 2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.13536, 0.509612, 2.427788, 0.101693, 2.616842, 1.0, -0.0, 1.0, -0.0, 1.0, 0.375, 0.5, 2.226569, 0.101693, 2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.36464, 0.509612, 2.226569, 0.101693, 2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.36464, 0.509612, 2.427788, 0.101693, -2.616842, 1.0, -0.0, 1.0, -0.0, 1.0, 0.375, 0.75, 2.226569, 0.101693, -2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.36464, 0.740388, 2.226569, 0.101693, -2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.36464, 0.740388, -2.427788, 0.101693, -2.616842, 1.0, -0.0, 1.0, -0.0, 1.0, 0.125, 0.75, -2.226569, 0.101693, -2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.13536, 0.740388, 2.226569, -0.107441, 2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.36464, 0.509612, -2.226569, -0.107442, -2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.13536, 0.740388, -2.226569, -0.107441, 2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.13536, 0.509612, -2.226569, 0.101693, 2.415624, 1.0, 1.0, -0.0, -0.0, 1.0, 0.13536, 0.509612, -2.226569, -0.107442, -2.415624, 1.0, 1.0, -0.0, -0.0, 1.0, 0.13536, 0.740388, -2.226569, 0.101693, -2.415624, 1.0, 1.0, -0.0, -0.0, 1.0, 0.13536, 0.740388, -2.226569, 0.101693, -2.415624, 1.0, -0.0, -0.0, 1.0, 1.0, 0.13536, 0.740388, 2.226569, -0.107442, -2.415624, 1.0, -0.0, -0.0, 1.0, 1.0, 0.36464, 0.740388, 2.226569, 0.101693, -2.415624, 1.0, -0.0, -0.0, 1.0, 1.0, 0.36464, 0.740388, 2.226569, 0.101693, 2.415624, 1.0, -0.0, -0.0, -1.0, 1.0, 0.36464, 0.509612, -2.226569, -0.107441, 2.415624, 1.0, -0.0, -0.0, -1.0, 1.0, 0.13536, 0.509612, -2.226569, 0.101693, 2.415624, 1.0, -0.0, -0.0, -1.0, 1.0, 0.13536, 0.509612, -2.427788, -0.29933, -2.616842, 1.0, -1.0, -0.0, -0.0, 1.0, 0.625, 0.0, -2.427788, -0.29933, 2.616842, 1.0, -1.0, -0.0, -0.0, 1.0, 0.625, 0.25, -2.427788, 0.101693, 2.616842, 1.0, -1.0, -0.0, -0.0, 1.0, 0.375, 0.25, -2.427788, -0.29933, 2.616842, 1.0, -0.0, -0.0, 1.0, 1.0, 0.625, 0.25, 2.427788, -0.29933, 2.616842, 1.0, -0.0, -0.0, 1.0, 1.0, 0.625, 0.5, 2.427788, 0.101693, 2.616842, 1.0, -0.0, -0.0, 1.0, 1.0, 0.375, 0.5, 2.427788, -0.29933, 2.616842, 1.0, 1.0, -0.0, -0.0, 1.0, 0.625, 0.5, 2.427788, -0.29933, -2.616842, 1.0, 1.0, -0.0, -0.0, 1.0, 0.625, 0.75, 2.427788, 0.101693, -2.616842, 1.0, 1.0, -0.0, -0.0, 1.0, 0.375, 0.75, 2.427788, -0.29933, -2.616842, 1.0, -0.0, -0.0, -1.0, 1.0, 0.625, 0.75, -2.427788, -0.29933, -2.616842, 1.0, -0.0, -0.0, -1.0, 1.0, 0.625, 1.0, -2.427788, 0.101693, -2.616842, 1.0, -0.0, -0.0, -1.0, 1.0, 0.375, 1.0, 2.226569, 0.101693, -2.415624, 1.0, -1.0, -0.0, -0.0, 1.0, 0.36464, 0.740388, 2.226569, -0.107442, -2.415624, 1.0, -1.0, -0.0, -0.0, 1.0, 0.36464, 0.740388, 2.226569, -0.107441, 2.415624, 1.0, -1.0, -0.0, -0.0, 1.0, 0.36464, 0.509612, -2.427788, -0.29933, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.875, 0.5, -2.427788, -0.29933, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.875, 0.75, 2.427788, -0.29933, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.625, 0.75, -2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.5, -2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.75, -2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.75, 2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.5, -2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.5, -2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.5, 2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.75, 2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.5, 2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.5, -2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.75, 2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.75, 2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.75, -2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.5, -2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.75, -2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.75, 2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.5, -2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.5, -2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.5, 2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.75, 2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.5, 2.427788, 0.101693, 2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.5, -2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.125, 0.75, 2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.75, 2.427788, 0.101693, -2.616842, 1.0, -0.0, -1.0, -0.0, 1.0, 0.375, 0.75, -2.226569, 0.101693, -2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.13536, 0.740388, -2.427788, 0.101693, -2.616842, 1.0, -0.0, 1.0, -0.0, 1.0, 0.125, 0.75, -2.427788, 0.101693, 2.616842, 1.0, -0.0, 1.0, -0.0, 1.0, 0.125, 0.5, -2.226569, 0.101693, 2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.13536, 0.509612, -2.427788, 0.101693, 2.616842, 1.0, -0.0, 1.0, -0.0, 1.0, 0.125, 0.5, 2.427788, 0.101693, 2.616842, 1.0, -0.0, 1.0, -0.0, 1.0, 0.375, 0.5, 2.226569, 0.101693, 2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.36464, 0.509612, 2.427788, 0.101693, 2.616842, 1.0, -0.0, 1.0, -0.0, 1.0, 0.375, 0.5, 2.427788, 0.101693, -2.616842, 1.0, -0.0, 1.0, -0.0, 1.0, 0.375, 0.75, 2.226569, 0.101693, -2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.36464, 0.740388, 2.427788, 0.101693, -2.616842, 1.0, -0.0, 1.0, -0.0, 1.0, 0.375, 0.75, -2.427788, 0.101693, -2.616842, 1.0, -0.0, 1.0, -0.0, 1.0, 0.125, 0.75, 2.226569, -0.107441, 2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.36464, 0.509612, 2.226569, -0.107442, -2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.36464, 0.740388, -2.226569, -0.107442, -2.415624, 1.0, -0.0, 1.0, -0.0, 1.0, 0.13536, 0.740388, -2.226569, 0.101693, 2.415624, 1.0, 1.0, -0.0, -0.0, 1.0, 0.13536, 0.509612, -2.226569, -0.107441, 2.415624, 1.0, 1.0, -0.0, -0.0, 1.0, 0.13536, 0.509612, -2.226569, -0.107442, -2.415624, 1.0, 1.0, -0.0, -0.0, 1.0, 0.13536, 0.740388, -2.226569, 0.101693, -2.415624, 1.0, -0.0, -0.0, 1.0, 1.0, 0.13536, 0.740388, -2.226569, -0.107442, -2.415624, 1.0, -0.0, -0.0, 1.0, 1.0, 0.13536, 0.740388, 2.226569, -0.107442, -2.415624, 1.0, -0.0, -0.0, 1.0, 1.0, 0.36464, 0.740388, 2.226569, 0.101693, 2.415624, 1.0, -0.0, -0.0, -1.0, 1.0, 0.36464, 0.509612, 2.226569, -0.107441, 2.415624, 1.0, -0.0, -0.0, -1.0, 1.0, 0.36464, 0.509612, -2.226569, -0.107441, 2.415624, 1.0, -0.0, -0.0, -1.0, 1.0, 0.13536, 0.509612};
    float combined[] = {4.115438, -0.861793, 5.086406, 1.0, -0.0, -0.0, -1.0, 1.0, 0.223051, 0.773862, -4.115437, 0.476233, 5.086406, 1.0, -0.0, -0.0, -1.0, 1.0, 0.776949, 0.976138, 4.115438, 0.476233, 5.086406, 1.0, -0.0, -0.0, -1.0, 1.0, 0.776949, 0.773862, 5.086406, -0.861793, -4.115438, 1.0, -1.0, -0.0, -0.0, 1.0, 0.223051, 0.523862, 5.086406, 0.476233, 4.115437, 1.0, -1.0, -0.0, -0.0, 1.0, 0.776949, 0.726138, 5.086406, 0.476233, -4.115438, 1.0, -1.0, -0.0, -0.0, 1.0, 0.776949, 0.523862, 3.389904, 0.109176, -3.389906, 1.0, 1.0, -0.0, -0.0, 1.0, 0.666692, 0.541692, 3.389904, 1.047503, 3.389903, 1.0, 1.0, -0.0, -0.0, 1.0, 0.666692, 0.708308, 3.389904, 0.109176, 3.389903, 1.0, 1.0, -0.0, -0.0, 1.0, 0.666692, 0.708308, -5.086405, -0.861793, 4.115437, 1.0, 1.0, -0.0, -0.0, 1.0, 0.223051, 0.023862, -5.086405, 0.476233, -4.115438, 1.0, 1.0, -0.0, -0.0, 1.0, 0.776949, 0.226138, -5.086405, 0.476233, 4.115437, 1.0, 1.0, -0.0, -0.0, 1.0, 0.776949, 0.023862, -4.115437, -0.861793, -5.086407, 1.0, -0.0, -0.0, 1.0, 1.0, 0.223051, 0.273862, 4.115438, 0.476233, -5.086407, 1.0, -0.0, -0.0, 1.0, 1.0, 0.776949, 0.476138, -4.115437, 0.476233, -5.086407, 1.0, -0.0, -0.0, 1.0, 1.0, 0.776949, 0.273862, -4.115437, -0.494736, 4.115437, 1.0, -0.5774, -0.5774, 0.5773, 1.0, 0.148862, 0.726138, -4.115437, 0.476233, 5.086406, 1.0, -0.5774, -0.5774, 0.5773, 1.0, 0.148862, 0.75, -5.086405, 0.476233, 4.115437, 1.0, -0.5774, -0.5774, 0.5773, 1.0, 0.125, 0.726138, -4.115437, -0.861793, 5.086406, 1.0, -0.5774, 0.5774, 0.5773, 1.0, 0.625, 0.976138, -4.115437, 0.109176, 4.115437, 1.0, -0.5774, 0.5774, 0.5773, 1.0, 0.625, 0.976138, -5.086405, -0.861793, 4.115437, 1.0, -0.5774, 0.5774, 0.5773, 1.0, 0.375, 1.0, -4.115437, -0.494736, -4.115438, 1.0, -0.5774, -0.5774, -0.5774, 1.0, 0.148862, 0.523862, -5.086405, 0.476233, -4.115438, 1.0, -0.5774, -0.5774, -0.5774, 1.0, 0.125, 0.523862, -4.115437, 0.476233, -5.086407, 1.0, -0.5774, -0.5774, -0.5774, 1.0, 0.148862, 0.5, -4.115437, 0.109176, -4.115438, 1.0, -0.5774, 0.5774, -0.5774, 1.0, 0.625, 0.273862, -4.115437, -0.861793, -5.086407, 1.0, -0.5774, 0.5774, -0.5774, 1.0, 0.625, 0.273862, -5.086405, -0.861793, -4.115438, 1.0, -0.5774, 0.5774, -0.5774, 1.0, 0.375, 0.25, 4.115438, -0.494736, 4.115437, 1.0, 0.5774, -0.5774, 0.5773, 1.0, 0.351138, 0.726138, 5.086406, 0.476233, 4.115437, 1.0, 0.5774, -0.5774, 0.5773, 1.0, 0.375, 0.726138, 4.115438, 0.476233, 5.086406, 1.0, 0.5774, -0.5774, 0.5773, 1.0, 0.351138, 0.75, 4.115438, 0.109176, 4.115437, 1.0, 0.5774, 0.5774, 0.5773, 1.0, 0.625, 0.773862, 4.115438, -0.861793, 5.086406, 1.0, 0.5774, 0.5774, 0.5773, 1.0, 0.625, 0.773862, 5.086406, -0.861793, 4.115437, 1.0, 0.5774, 0.5774, 0.5773, 1.0, 0.375, 0.75, 4.115438, -0.494736, -4.115438, 1.0, 0.5774, -0.5774, -0.5774, 1.0, 0.351138, 0.523862, 4.115438, 0.476233, -5.086407, 1.0, 0.5774, -0.5774, -0.5774, 1.0, 0.351138, 0.5, 5.086406, 0.476233, -4.115438, 1.0, 0.5774, -0.5774, -0.5774, 1.0, 0.375, 0.523862, 4.115438, 0.109176, -4.115438, 1.0, 0.5774, 0.5774, -0.5774, 1.0, 0.625, 0.523862, 5.086406, -0.861793, -4.115438, 1.0, 0.5774, 0.5774, -0.5774, 1.0, 0.625, 0.523862, 4.115438, -0.861793, -5.086407, 1.0, 0.5774, 0.5774, -0.5774, 1.0, 0.375, 0.5, -4.115437, -0.494736, 4.115437, 1.0, -0.7071, -0.7071, -0.0, 1.0, 0.148862, 0.726138, -5.086405, 0.476233, -4.115438, 1.0, -0.7071, -0.7071, -0.0, 1.0, 0.125, 0.523862, -4.115437, -0.494736, -4.115438, 1.0, -0.7071, -0.7071, -0.0, 1.0, 0.148862, 0.523862, -4.115437, -0.861793, 5.086406, 1.0, 0.7071, -0.0, -0.7071, 1.0, 0.375, 0.0, -5.086405, 0.476233, 4.115437, 1.0, 0.7071, -0.0, -0.7071, 1.0, 0.776949, 0.023862, -4.115437, 0.476233, 5.086406, 1.0, 0.7071, -0.0, -0.7071, 1.0, 0.625, 0.0, -4.115437, 0.109176, -4.115438, 1.0, -0.7071, 0.7071, -0.0, 1.0, 0.625, 0.226138, -5.086405, -0.861793, 4.115437, 1.0, -0.7071, 0.7071, -0.0, 1.0, 0.223051, 0.023862, -4.115437, 0.109176, 4.115437, 1.0, -0.7071, 0.7071, -0.0, 1.0, 0.625, 0.023862, -4.115437, 0.476233, -5.086407, 1.0, 0.7071, -0.0, 0.7071, 1.0, 0.776949, 0.273862, -5.086405, -0.861793, -4.115438, 1.0, 0.7071, -0.0, 0.7071, 1.0, 0.223051, 0.226138, -4.115437, -0.861793, -5.086407, 1.0, 0.7071, -0.0, 0.7071, 1.0, 0.223051, 0.273862, -4.115437, -0.494736, -4.115438, 1.0, -0.0, -0.7071, -0.7071, 1.0, 0.148862, 0.523862, 4.115438, 0.476233, -5.086407, 1.0, -0.0, -0.7071, -0.7071, 1.0, 0.351138, 0.5, 4.115438, -0.494736, -4.115438, 1.0, -0.0, -0.7071, -0.7071, 1.0, 0.351138, 0.523862, 4.115438, 0.109176, -4.115438, 1.0, -0.0, 0.7071, -0.7071, 1.0, 0.625, 0.476138, -4.115437, -0.861793, -5.086407, 1.0, -0.0, 0.7071, -0.7071, 1.0, 0.223051, 0.273862, -4.115437, 0.109176, -4.115438, 1.0, -0.0, 0.7071, -0.7071, 1.0, 0.625, 0.273862, 5.086406, -0.861793, -4.115438, 1.0, -0.7071, -0.0, 0.7071, 1.0, 0.223051, 0.523862, 4.115438, 0.476233, -5.086407, 1.0, -0.7071, -0.0, 0.7071, 1.0, 0.776949, 0.476138, 4.115438, -0.861793, -5.086407, 1.0, -0.7071, -0.0, 0.7071, 1.0, 0.223051, 0.476138, 4.115438, -0.494736, -4.115438, 1.0, 0.7071, -0.7071, -0.0, 1.0, 0.351138, 0.523862, 5.086406, 0.476233, 4.115437, 1.0, 0.7071, -0.7071, -0.0, 1.0, 0.776949, 0.726138, 4.115438, -0.494736, 4.115437, 1.0, 0.7071, -0.7071, -0.0, 1.0, 0.351138, 0.726138, 4.115438, 0.109176, 4.115437, 1.0, 0.7071, 0.7071, -0.0, 1.0, 0.648862, 0.726138, 5.086406, -0.861793, -4.115438, 1.0, 0.7071, 0.7071, -0.0, 1.0, 0.223051, 0.523862, 4.115438, 0.109176, -4.115438, 1.0, 0.7071, 0.7071, -0.0, 1.0, 0.648862, 0.523862, 4.115438, 0.476233, 5.086406, 1.0, -0.7071, -0.0, -0.7071, 1.0, 0.776949, 0.773862, 5.086406, -0.861793, 4.115437, 1.0, -0.7071, -0.0, -0.7071, 1.0, 0.223051, 0.726138, 4.115438, -0.861793, 5.086406, 1.0, -0.7071, -0.0, -0.7071, 1.0, 0.223051, 0.773862, 4.115438, -0.494736, 4.115437, 1.0, -0.0, -0.7071, 0.7071, 1.0, 0.351138, 0.726138, -4.115437, 0.476233, 5.086406, 1.0, -0.0, -0.7071, 0.7071, 1.0, 0.148862, 0.75, -4.115437, -0.494736, 4.115437, 1.0, -0.0, -0.7071, 0.7071, 1.0, 0.148862, 0.726138, -4.115437, 0.109176, 4.115437, 1.0, -0.0, 0.7071, 0.7071, 1.0, 0.625, 0.976138, 4.115438, -0.861793, 5.086406, 1.0, -0.0, 0.7071, 0.7071, 1.0, 0.223051, 0.773862, 4.115438, 0.109176, 4.115437, 1.0, -0.0, 0.7071, 0.7071, 1.0, 0.625, 0.773862, 4.115438, -0.494736, -4.115438, 1.0, -0.0, -1.0, -0.0, 1.0, 0.351138, 0.523862, -4.115437, -0.494736, 4.115437, 1.0, -0.0, -1.0, -0.0, 1.0, 0.148862, 0.726138, -4.115437, -0.494736, -4.115438, 1.0, -0.0, -1.0, -0.0, 1.0, 0.148862, 0.523862, -3.389904, 0.109176, 3.389903, 1.0, -0.0, 1.0, -0.0, 1.0, 0.833308, 0.708308, -4.115437, 0.109176, -4.115438, 1.0, -0.0, 1.0, -0.0, 1.0, 0.851138, 0.523862, -4.115437, 0.109176, 4.115437, 1.0, -0.0, 1.0, -0.0, 1.0, 0.851138, 0.726138, 3.389904, 0.109176, -3.389906, 1.0, -0.0, 1.0, -0.0, 1.0, 0.666692, 0.541692, -4.115437, 0.109176, -4.115438, 1.0, -0.0, 1.0, -0.0, 1.0, 0.851138, 0.523862, -3.389904, 0.109176, -3.389906, 1.0, -0.0, 1.0, -0.0, 1.0, 0.833308, 0.541692, 3.389904, 0.109176, 3.389903, 1.0, -0.0, 1.0, -0.0, 1.0, 0.666692, 0.708308, 4.115438, 0.109176, -4.115438, 1.0, -0.0, 1.0, -0.0, 1.0, 0.648862, 0.523862, 3.389904, 0.109176, -3.389906, 1.0, -0.0, 1.0, -0.0, 1.0, 0.666692, 0.541692, -3.389904, 0.109176, 3.389903, 1.0, -0.0, 1.0, -0.0, 1.0, 0.833308, 0.708308, 4.115438, 0.109176, 4.115437, 1.0, -0.0, 1.0, -0.0, 1.0, 0.648862, 0.726138, 3.389904, 0.109176, 3.389903, 1.0, -0.0, 1.0, -0.0, 1.0, 0.666692, 0.708308, -3.389904, 1.047503, -3.389906, 1.0, -0.0, 1.0, -0.0, 1.0, 0.833308, 0.541692, 3.389904, 1.047503, 3.389903, 1.0, -0.0, 1.0, -0.0, 1.0, 0.666692, 0.708308, 3.389904, 1.047503, -3.389906, 1.0, -0.0, 1.0, -0.0, 1.0, 0.666692, 0.541692, -3.389904, 0.109176, 3.389903, 1.0, -1.0, -0.0, -0.0, 1.0, 0.833308, 0.708308, -3.389904, 1.047503, -3.389906, 1.0, -1.0, -0.0, -0.0, 1.0, 0.833308, 0.541692, -3.389904, 0.109176, -3.389906, 1.0, -1.0, -0.0, -0.0, 1.0, 0.833308, 0.541692, 3.389904, 0.109176, 3.389903, 1.0, -0.0, -0.0, 1.0, 1.0, 0.666692, 0.708308, -3.389904, 1.047503, 3.389903, 1.0, -0.0, -0.0, 1.0, 1.0, 0.833308, 0.708308, -3.389904, 0.109176, 3.389903, 1.0, -0.0, -0.0, 1.0, 1.0, 0.833308, 0.708308, -3.389904, 0.109176, -3.389906, 1.0, -0.0, -0.0, -1.0, 1.0, 0.833308, 0.541692, 3.389904, 1.047503, -3.389906, 1.0, -0.0, -0.0, -1.0, 1.0, 0.666692, 0.541692, 3.389904, 0.109176, -3.389906, 1.0, -0.0, -0.0, -1.0, 1.0, 0.666692, 0.541692, 4.115438, -0.861793, 5.086406, 1.0, -0.0, -0.0, -1.0, 1.0, 0.223051, 0.773862, -4.115437, -0.861793, 5.086406, 1.0, -0.0, -0.0, -1.0, 1.0, 0.223051, 0.976138, -4.115437, 0.476233, 5.086406, 1.0, -0.0, -0.0, -1.0, 1.0, 0.776949, 0.976138, 5.086406, -0.861793, -4.115438, 1.0, -1.0, -0.0, -0.0, 1.0, 0.223051, 0.523862, 5.086406, -0.861793, 4.115437, 1.0, -1.0, -0.0, -0.0, 1.0, 0.223051, 0.726138, 5.086406, 0.476233, 4.115437, 1.0, -1.0, -0.0, -0.0, 1.0, 0.776949, 0.726138, 3.389904, 0.109176, -3.389906, 1.0, 1.0, -0.0, -0.0, 1.0, 0.666692, 0.541692, 3.389904, 1.047503, -3.389906, 1.0, 1.0, -0.0, -0.0, 1.0, 0.666692, 0.541692, 3.389904, 1.047503, 3.389903, 1.0, 1.0, -0.0, -0.0, 1.0, 0.666692, 0.708308, -5.086405, -0.861793, 4.115437, 1.0, 1.0, -0.0, -0.0, 1.0, 0.223051, 0.023862, -5.086405, -0.861793, -4.115438, 1.0, 1.0, -0.0, -0.0, 1.0, 0.223051, 0.226138, -5.086405, 0.476233, -4.115438, 1.0, 1.0, -0.0, -0.0, 1.0, 0.776949, 0.226138, -4.115437, -0.861793, -5.086407, 1.0, -0.0, -0.0, 1.0, 1.0, 0.223051, 0.273862, 4.115438, -0.861793, -5.086407, 1.0, -0.0, -0.0, 1.0, 1.0, 0.223051, 0.476138, 4.115438, 0.476233, -5.086407, 1.0, -0.0, -0.0, 1.0, 1.0, 0.776949, 0.476138, -4.115437, -0.494736, 4.115437, 1.0, -0.7071, -0.7071, -0.0, 1.0, 0.148862, 0.726138, -5.086405, 0.476233, 4.115437, 1.0, -0.7071, -0.7071, -0.0, 1.0, 0.125, 0.726138, -5.086405, 0.476233, -4.115438, 1.0, -0.7071, -0.7071, -0.0, 1.0, 0.125, 0.523862, -4.115437, -0.861793, 5.086406, 1.0, 0.7071, -0.0, -0.7071, 1.0, 0.375, 0.0, -5.086405, -0.861793, 4.115437, 1.0, 0.7071, -0.0, -0.7071, 1.0, 0.223051, 0.023862, -5.086405, 0.476233, 4.115437, 1.0, 0.7071, -0.0, -0.7071, 1.0, 0.776949, 0.023862, -4.115437, 0.109176, -4.115438, 1.0, -0.7071, 0.7071, -0.0, 1.0, 0.625, 0.226138, -5.086405, -0.861793, -4.115438, 1.0, -0.7071, 0.7071, -0.0, 1.0, 0.223051, 0.226138, -5.086405, -0.861793, 4.115437, 1.0, -0.7071, 0.7071, -0.0, 1.0, 0.223051, 0.023862, -4.115437, 0.476233, -5.086407, 1.0, 0.7071, -0.0, 0.7071, 1.0, 0.776949, 0.273862, -5.086405, 0.476233, -4.115438, 1.0, 0.7071, -0.0, 0.7071, 1.0, 0.776949, 0.226138, -5.086405, -0.861793, -4.115438, 1.0, 0.7071, -0.0, 0.7071, 1.0, 0.223051, 0.226138, -4.115437, -0.494736, -4.115438, 1.0, -0.0, -0.7071, -0.7071, 1.0, 0.148862, 0.523862, -4.115437, 0.476233, -5.086407, 1.0, -0.0, -0.7071, -0.7071, 1.0, 0.148862, 0.5, 4.115438, 0.476233, -5.086407, 1.0, -0.0, -0.7071, -0.7071, 1.0, 0.351138, 0.5, 4.115438, 0.109176, -4.115438, 1.0, -0.0, 0.7071, -0.7071, 1.0, 0.625, 0.476138, 4.115438, -0.861793, -5.086407, 1.0, -0.0, 0.7071, -0.7071, 1.0, 0.223051, 0.476138, -4.115437, -0.861793, -5.086407, 1.0, -0.0, 0.7071, -0.7071, 1.0, 0.223051, 0.273862, 5.086406, -0.861793, -4.115438, 1.0, -0.7071, -0.0, 0.7071, 1.0, 0.223051, 0.523862, 5.086406, 0.476233, -4.115438, 1.0, -0.7071, -0.0, 0.7071, 1.0, 0.776949, 0.523862, 4.115438, 0.476233, -5.086407, 1.0, -0.7071, -0.0, 0.7071, 1.0, 0.776949, 0.476138, 4.115438, -0.494736, -4.115438, 1.0, 0.7071, -0.7071, -0.0, 1.0, 0.351138, 0.523862, 5.086406, 0.476233, -4.115438, 1.0, 0.7071, -0.7071, -0.0, 1.0, 0.776949, 0.523862, 5.086406, 0.476233, 4.115437, 1.0, 0.7071, -0.7071, -0.0, 1.0, 0.776949, 0.726138, 4.115438, 0.109176, 4.115437, 1.0, 0.7071, 0.7071, -0.0, 1.0, 0.648862, 0.726138, 5.086406, -0.861793, 4.115437, 1.0, 0.7071, 0.7071, -0.0, 1.0, 0.223051, 0.726138, 5.086406, -0.861793, -4.115438, 1.0, 0.7071, 0.7071, -0.0, 1.0, 0.223051, 0.523862, 4.115438, 0.476233, 5.086406, 1.0, -0.7071, -0.0, -0.7071, 1.0, 0.776949, 0.773862, 5.086406, 0.476233, 4.115437, 1.0, -0.7071, -0.0, -0.7071, 1.0, 0.776949, 0.726138, 5.086406, -0.861793, 4.115437, 1.0, -0.7071, -0.0, -0.7071, 1.0, 0.223051, 0.726138, 4.115438, -0.494736, 4.115437, 1.0, -0.0, -0.7071, 0.7071, 1.0, 0.351138, 0.726138, 4.115438, 0.476233, 5.086406, 1.0, -0.0, -0.7071, 0.7071, 1.0, 0.351138, 0.75, -4.115437, 0.476233, 5.086406, 1.0, -0.0, -0.7071, 0.7071, 1.0, 0.148862, 0.75, -4.115437, 0.109176, 4.115437, 1.0, -0.0, 0.7071, 0.7071, 1.0, 0.625, 0.976138, -4.115437, -0.861793, 5.086406, 1.0, -0.0, 0.7071, 0.7071, 1.0, 0.223051, 0.976138, 4.115438, -0.861793, 5.086406, 1.0, -0.0, 0.7071, 0.7071, 1.0, 0.223051, 0.773862, 4.115438, -0.494736, -4.115438, 1.0, -0.0, -1.0, -0.0, 1.0, 0.351138, 0.523862, 4.115438, -0.494736, 4.115437, 1.0, -0.0, -1.0, -0.0, 1.0, 0.351138, 0.726138, -4.115437, -0.494736, 4.115437, 1.0, -0.0, -1.0, -0.0, 1.0, 0.148862, 0.726138, -3.389904, 0.109176, 3.389903, 1.0, -0.0, 1.0, -0.0, 1.0, 0.833308, 0.708308, -3.389904, 0.109176, -3.389906, 1.0, -0.0, 1.0, -0.0, 1.0, 0.833308, 0.541692, -4.115437, 0.109176, -4.115438, 1.0, -0.0, 1.0, -0.0, 1.0, 0.851138, 0.523862, 3.389904, 0.109176, -3.389906, 1.0, -0.0, 1.0, -0.0, 1.0, 0.666692, 0.541692, 4.115438, 0.109176, -4.115438, 1.0, -0.0, 1.0, -0.0, 1.0, 0.648862, 0.523862, -4.115437, 0.109176, -4.115438, 1.0, -0.0, 1.0, -0.0, 1.0, 0.851138, 0.523862, 3.389904, 0.109176, 3.389903, 1.0, -0.0, 1.0, -0.0, 1.0, 0.666692, 0.708308, 4.115438, 0.109176, 4.115437, 1.0, -0.0, 1.0, -0.0, 1.0, 0.648862, 0.726138, 4.115438, 0.109176, -4.115438, 1.0, -0.0, 1.0, -0.0, 1.0, 0.648862, 0.523862, -3.389904, 0.109176, 3.389903, 1.0, -0.0, 1.0, -0.0, 1.0, 0.833308, 0.708308, -4.115437, 0.109176, 4.115437, 1.0, -0.0, 1.0, -0.0, 1.0, 0.851138, 0.726138, 4.115438, 0.109176, 4.115437, 1.0, -0.0, 1.0, -0.0, 1.0, 0.648862, 0.726138, -3.389904, 1.047503, -3.389906, 1.0, -0.0, 1.0, -0.0, 1.0, 0.833308, 0.541692, -3.389904, 1.047503, 3.389903, 1.0, -0.0, 1.0, -0.0, 1.0, 0.833308, 0.708308, 3.389904, 1.047503, 3.389903, 1.0, -0.0, 1.0, -0.0, 1.0, 0.666692, 0.708308, -3.389904, 0.109176, 3.389903, 1.0, -1.0, -0.0, -0.0, 1.0, 0.833308, 0.708308, -3.389904, 1.047503, 3.389903, 1.0, -1.0, -0.0, -0.0, 1.0, 0.833308, 0.708308, -3.389904, 1.047503, -3.389906, 1.0, -1.0, -0.0, -0.0, 1.0, 0.833308, 0.541692, 3.389904, 0.109176, 3.389903, 1.0, -0.0, -0.0, 1.0, 1.0, 0.666692, 0.708308, 3.389904, 1.047503, 3.389903, 1.0, -0.0, -0.0, 1.0, 1.0, 0.666692, 0.708308, -3.389904, 1.047503, 3.389903, 1.0, -0.0, -0.0, 1.0, 1.0, 0.833308, 0.708308, -3.389904, 0.109176, -3.389906, 1.0, -0.0, -0.0, -1.0, 1.0, 0.833308, 0.541692, -3.389904, 1.047503, -3.389906, 1.0, -0.0, -0.0, -1.0, 1.0, 0.833308, 0.541692, 3.389904, 1.047503, -3.389906, 1.0, -0.0, -0.0, -1.0, 1.0, 0.666692, 0.541692};

    unsigned int indices[verticesCount];
    for (int i = 0; i < verticesCount; i++)
    {
        indices[i] = i;
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

    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("textures/stone2.jpg", &width, &height, &nrChannels, 0);
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

    glBindBuffer(GL_ARRAY_BUFFER, 0);         // unbind VBO
    glBindVertexArray(0);                     // unbind VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind EBO
}

void Base::draw()
{
    shaderProgram.use();

    glUniform1i(shaderProgram.getUniformLocation("texture1"), 1);

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
    model = glm::scale(model, glm::vec3(2.0f, 0.5f, 2.0f));

    glUniformMatrix4fv(shaderProgram.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}