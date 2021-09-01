#version 330

uniform sampler2D u_Texture; // The texture to be read from by this shader

in vec3 fs_Nor;
in vec3 fs_LightVec;

layout(location = 0) out vec3 out_Col;

void main()
{
    // TODO Homework 4
    vec3 n = normalize(fs_Nor);
    vec3 l = normalize(fs_LightVec);

    float t = clamp(dot(n, l), 0, 1);

    // color pallete
    vec3 a = vec3(0.5, 0.25, 0.75);
    vec3 b = vec3(0.15, 0.5, 0.5);
    vec3 c = vec3(0.85, 0.5, 0.15);
    vec3 d = vec3(0.4, 0.15, 0.25);

    out_Col = a + b * cos(2 * 3.141925 * (c * t + d));
}
