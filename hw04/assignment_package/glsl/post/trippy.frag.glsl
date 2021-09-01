#version 150

uniform ivec2 u_Dimensions;
uniform int u_Time;

in vec2 fs_UV;

out vec3 color;

uniform sampler2D u_RenderedTexture;

void main()
{
    vec2 uv = fs_UV;

    float interval = (smoothstep(-1, 1, sin(u_Time * 0.015))) + 0.5;

    // for trippy wave thing
    float xOffset = uv.x * (cos(u_Time * 3.1415926 + uv.y)) / 100000;
    float yOffset = uv.y * (cos(u_Time * 3 + 50* uv.y)) / 50;

    float xTrippy = (xOffset / interval) + uv.x;
    float yTrippy = (-yOffset/interval) - (0.01 - uv.y);

    vec2 trippy = vec2(xTrippy, yTrippy);

    vec3 trippyOffset = vec3(texture(u_RenderedTexture, trippy));

    trippyOffset /= (interval * 2.5);

    // rendering the red, green, and blue channels of the image at different offsets
    vec2 size = vec2(textureSize(u_RenderedTexture, 0));

    float offset = 20 / size.x;

    // offsetting color
    vec2 redOffset = vec2(uv.x + offset, uv.y);
    vec2 greenOffset = vec2(uv.x - offset, uv.y);
    vec2 blueOffset = vec2(uv.x, uv.y + offset);

    vec3 colorOffset = vec3(texture(u_RenderedTexture, redOffset).r,
                            texture(u_RenderedTexture, greenOffset).g,
                            texture(u_RenderedTexture, blueOffset).b);

    color = trippyOffset + colorOffset;
}
