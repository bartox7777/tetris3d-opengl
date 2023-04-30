#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

layout (location = 0) in vec3 position;

void main() {
    gl_Position = perspective * view * model * vec4(position, 1.0);
}