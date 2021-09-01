#version 330

uniform sampler2D u_Texture; // The texture to be read from by this shader
uniform int u_Time;

in vec3 fs_Pos;
in vec3 fs_Nor;
in vec3 fs_LightVec;

layout(location = 0) out vec3 out_Col;

void main()
{
    // TODO Homework 4
    vec3 n = normalize(fs_Nor);
    vec3 l = normalize(fs_LightVec);

    float t = clamp(dot(n, l), 0, 1);

    t *= sin(u_Time * 0.05);

    // color palette
    vec3 a = vec3(0.5, 0.5, 0.75) - t;
    vec3 b = vec3(0.25, 0.5, 0.5) + t;
    vec3 c = vec3(0.65, 0.5, 0.15) - t;
    vec3 d = vec3(0.4, 0.25, 0.25) + t;

    out_Col = a + b * cos(2 * 3.141925 * (c * t + d));
}
