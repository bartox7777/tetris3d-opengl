#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;
layout (location = 2) in vec2 texCoord;

struct Light {
    vec4 l;
    vec4 v;
    vec4 n;
};

#define lightSourceCount 2

out vec2 otexCoord;
out Light olights[lightSourceCount];

Light lights[lightSourceCount];

void main() {
    vec4 lps[lightSourceCount] = vec4[lightSourceCount](vec4(0, 3, -6, 1), vec4(0, 3, 6, 1));

    for (int i=0; i<lightSourceCount; i++){
        lights[i] = Light(normalize(view * lps[i] - view*model*position), normalize(vec4(0, 0, 0, 1) - view * model * position), normalize(view * model * normal));
    }

    olights = lights;

    gl_Position = perspective * view * model * position;
    otexCoord = vec2(texCoord.x, texCoord.y);
}