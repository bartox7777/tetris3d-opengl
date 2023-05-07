#version 330 core

in vec4 ocolor;
in vec2 otexCoord;

out vec4 color;

uniform sampler2D texture1;

void main() {
    color = mix(texture(texture1, otexCoord), ocolor, 0.2);
    // color = ocolor;
}