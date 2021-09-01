#version 150

in vec2 fs_UV;

out vec3 color;

uniform sampler2D u_RenderedTexture;

void main()
{
    // TODO Homework 5

    // grey scale
    vec4 colorScale = texture(u_RenderedTexture, fs_UV);

    float grey = 0.21 * colorScale.x + 0.72 * colorScale.y + 0.07 * colorScale.z;

    // vignette
    vec2 pt = vec2(0.5, 0.5);   // center

    float dist = distance(fs_UV, pt);

    color = vec3(grey - dist);
}
