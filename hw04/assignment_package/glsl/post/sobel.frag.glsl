#version 150

in vec2 fs_UV;

out vec3 color;

uniform sampler2D u_RenderedTexture;
uniform int u_Time;
uniform ivec2 u_Dimensions;

void main()
{

    float x = 1.f / u_Dimensions.x;
    float y = 1.f / u_Dimensions.y;

    const float hKernel[] = float[9](3, 0, -3,
                                     10, 0, -10,
                                     3, 0, -3);

    const float vKernel[] = float[9](3, 10, 3,
                                     0, 0, 0,
                                     -3, -10, -3);

    vec3 hGradient = vec3(0);
    vec3 vGradient = vec3(0);

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            vec2 neighbor = vec2(j * x, i * y);
            vec3 c = texture(u_RenderedTexture, fs_UV + neighbor).rgb;
            hGradient += hKernel[(j + 1) + (i + 1) * 3] * c;
            vGradient += vKernel[(j + 1) + (i + 1) * 3] * c;
        }
    }

    color = vec3(sqrt(vGradient * vGradient + hGradient * hGradient));
}

