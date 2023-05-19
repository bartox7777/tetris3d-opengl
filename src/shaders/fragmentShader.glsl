#version 330 core

struct Light {
    vec4 l;
    vec4 v;
    vec4 n;
};

#define lightSourceCount 2

uniform vec4 ocolor;
in vec2 otexCoord;
in Light olights[lightSourceCount];

out vec4 color;

uniform sampler2D texture1;

void main() {
    float nl = 0.0;
    float rv = 0.0;
    for (int i=0; i<lightSourceCount; i++){
        vec4 l = normalize(olights[i].l);
        vec4 v = normalize(olights[i].v);
        vec4 n = normalize(olights[i].n);

        vec4 r = reflect(-l, n);

        nl += clamp(dot(n, l), 0.2, 1.0);
        rv += pow(clamp(dot(r, v), 0.0, 1.0), 50.0);
    }

    vec4 c = mix(texture(texture1, otexCoord), ocolor, 0.2);

    color = vec4(c.rgb * nl, c.a) + vec4(vec3(rv)*0.2, 0);
    // color = ocolor;
}