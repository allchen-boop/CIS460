#version 150

uniform mat4 u_Model;
uniform mat3 u_ModelInvTr;
uniform mat4 u_View;
uniform mat4 u_Proj;

uniform int u_Time;

in vec4 vs_Pos;
in vec4 vs_Nor;

out vec3 fs_Pos;
out vec3 fs_Nor;
out vec3 fs_LightVec;

// helper functions from homework writeup
float mod289(float x) {
    return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 mod289(vec4 x) {
    return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 perm(vec4 x) {
    return mod289(((x * 34.0) + 1.0) * x);
}

float noise(vec3 p) {
    vec3 a = floor(p);
    vec3 d = p - a;
    d = d * d * (3.0 - 2.0 * d);

    vec4 b = vec4(a.xxy, a.y) + vec4(0.0, 1.0, 0.0, 1.0);
    vec4 k1 = perm(b.xyxy);
    vec4 k2 = perm(k1.xyxy + b.zzww);

    vec4 c = k2 + vec4(a.zzz, a.z);
    vec4 k3 = perm(c);
    vec4 k4 = perm(c + 1.0);

    vec4 o1 = fract(k3 * (1.0 / 41.0));
    vec4 o2 = fract(k4 * (1.0 / 41.0));

    vec4 o3 = o2 * d.z + o1 * (1.0 - d.z);
    vec2 o4 = o3.yw * d.x + o3.xz * (1.0 - d.x);

    return o4.y * d.y + o4.x * (1.0 - d.y);
}

void main()
{
    // TODO Homework 4

    fs_Nor = normalize(u_ModelInvTr * vec3(vs_Nor));

    float interval = (smoothstep(-1, 1, sin(u_Time * 3.14159 / 100.f)));

    vec3 displacementDirection = normalize(vec3(vs_Pos));

    // object is going to deform in deflated sphere like shape
    vec4 displacement = vec4(3.f * displacementDirection - vec3(vs_Pos), 1);

    float xDisplacement = pow(3, 2) / 10 * (sin(u_Time * 0.1) + 1);
    float yDisplacement = (cos(u_Time  * 0.1) + 1) / 2;

    displacement.x *= xDisplacement;
    displacement.y *= yDisplacement;
    displacement.z *= yDisplacement;

    vec4 newPosition = vec4(vec3(displacement) * displacementDirection, 1);

    // noise for each direction of new position
    newPosition += vec4(noise(vec3(newPosition)),
                        noise(vec3(newPosition)),
                        noise(vec3(newPosition)), 1);

    vec4 modelposition = u_Model * (vs_Pos + interval + displacement);

    fs_Pos = vec3(newPosition);

    vec4 light = (inverse(u_View) * vec4(0, 0, 0, 1)) - modelposition;
    fs_LightVec = vec3(light);

    gl_Position = u_Proj * u_View * modelposition;
}
