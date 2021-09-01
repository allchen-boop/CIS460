#version 150

uniform ivec2 u_Dimensions;
uniform int u_Time;

in vec2 fs_UV;

out vec3 color;

uniform sampler2D u_RenderedTexture;

// all helper functions taken from lecture slides
vec2 random2(vec2 p) {
    return fract(sin(vec2(dot(p, vec2(127.1, 311.7)), dot(p, vec2(269.5, 183.3)))) * 43758.5453);
}

vec3 random3(vec2 p) {
    return fract(sin(vec3(dot(p,vec2(127.1, 311.7)),
                          dot(p,vec2(269.5, 183.3)),
                          dot(p, vec2(420.6, 631.2)))) * 43758.5453);
}

// exactly from the slides
float interpNoise2D(float x, float y) {
    int intX = int(floor(x));
    float fractX = fract(x);
    int intY = int(floor(y));
    float fractY = fract(y);

    vec2 v1 = random2(vec2(intX, intY));
    vec2 v2 = random2(vec2(intX + 1, intY));
    vec2 v3 = random2(vec2(intX, intY + 1));
    vec2 v4 = random2(vec2(intX + 1, intY + 1));

    float i1 = mix(v1.x, v2.x, fractX);
    float i2 = mix(v3.x, v4.x, fractX);
    return mix(i1, i2, fractY);
}

// slightly modified from slides
float fbm(float x, float y) {
    float total = 0;
    float persistence = 0.6;
    int octaves = 5;

    for (int i = 1; i <= octaves; i++) {
        float freq = pow(2, i);
        float amp = pow(persistence, i);

        amp += (fs_UV.y / 2);
        total += interpNoise2D(x * freq, y * freq) * amp;
    }
    return total;
}

// from slides
float worleyNeighbor(float minDist, vec2 uvInt, vec2 uvFract) {
    for (int y = -1; y < 2; ++y) {
        for (int x = -1; x < 2; ++x) {

            // direction in which neighbor cell lies
            vec3 neighbor = vec3(float(x), float(y), 0);

            // Voronoi centerpoint for the neighboring cell
            vec3 point = random3(uvInt + vec2(neighbor));

            // distance between fragment coord and neighbor’s Voronoi point
            vec2 diff = vec2(neighbor + point) - uvFract;

            float dist = length(diff);
            minDist = min(minDist, dist);
        }
    }
    return minDist;
}

// for large moving reflections in background
float WorleyNoiseOne(vec2 uv) {
    uv *= 2;
    vec2 uvInt = floor(uv);
    vec2 uvFract = fract(uv);
    float minDist = 1.0;

    return worleyNeighbor(minDist, uvInt, uvFract);
}

// for noise altering color overlay
float WorleyNoiseTwo(float scale, float col) {
    vec2 uv = fs_UV * scale;
    vec2 uvInt = floor(uv);
    vec2 uvFract = fract(uv);
    float minDist = col;

    return worleyNeighbor(minDist, uvInt, uvFract);
}

void main()
{
    float x = 1.f / u_Dimensions.x;
    float y = 1.f / u_Dimensions.y;

    // worley noise gradient (from homework writup suggestion)
    vec2 rUv = vec2(x, 0);
    vec2 lUv = vec2(-x, 0);
    float rWorley =  WorleyNoiseOne(rUv + fs_UV);
    float lWorley = WorleyNoiseOne(lUv + fs_UV);
    float xGradient = (rWorley - lWorley) / (x + x);

    vec2 dUv = vec2(0, y);
    vec2 uUv = vec2(0, -y);
    float downWorely = WorleyNoiseOne(dUv + fs_UV);
    float upWorley = WorleyNoiseOne(uUv + fs_UV);
    float yGradient = (downWorely - upWorley) / (y + y);

    // current color
    color = texture(u_RenderedTexture, fs_UV).rgb;
    float col = color.r * 0.2 + color.g * 0.3 + color.b * 0.1;

    float background = fbm(WorleyNoiseOne(fs_UV), WorleyNoiseOne(fs_UV));
    float overlay =  WorleyNoiseTwo(300, col);

    float interval = 0.5 + (smoothstep(-2, 2, abs(sin(u_Time * 0.015))) * 2.5);

    float gradient = sqrt(xGradient * xGradient + yGradient * yGradient);

    vec2 uv = vec2(background / overlay * interval * x + gradient / 100,
                   background / overlay * interval * y + gradient / 100);

    color = vec3(texture(u_RenderedTexture, uv));
}
