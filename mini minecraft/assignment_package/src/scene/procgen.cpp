#include "procgen.h"

#include <math.h>
#include <iostream>
#include <glm_includes.h>

const float PI = 3.141593;

ProcGen::ProcGen() {}

ProcGen::~ProcGen() {}

int ProcGen::getHeight(int x, int z) {
    float grass = grasslands(x, z);
    float mtn = mountains(x, z);

    float perlin = glm::smoothstep(0.8, 0.9, (double)(fbm2D(x/2048.f, z/2048.f, 0.1))+1)/2;

    return glm::mix(grass, mtn, perlin);
}

float ProcGen::mountains(float x, float z) {
    x /= 128;
    z /= 128;

    int mountainMin = 140;
    int mountainMax = 250;

    return mountainMin + (mountainMax - mountainMin) * worleyNoise(x, z);
}

float ProcGen::grasslands(float x, float z) {
    x /= 1024;
    z /= 1024;

    int grassMin = 128;
    int grassMax = 140;

    return grassMin + (grassMax - grassMin) * (fbm2D(x, z, 0.1) + 1) / 2;
}

float ProcGen::worleyNoise(float x, float z) {
    float intX, fractX;
    fractX = modf(x, &intX);

    float intZ, fractZ;
    fractZ = modf(z, &intZ);

    float minDist1 = 1;
    float minDist2 = 1;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            glm::vec2 neighborDirection = glm::vec2(j, i);
            glm::vec2 neighborVoronoiCtr = voronoiCenter(glm::vec2(intX, intZ) + neighborDirection);
            glm::vec2 diff = neighborDirection + neighborVoronoiCtr - glm::vec2(fractX, fractZ);

            float dist = glm::length(diff);

            if (dist < minDist1) {
                minDist2 = minDist1;
                minDist1 = dist;
            } else if (dist < minDist2) {
                minDist2 = dist;
            }
        }
    }

    return minDist2 - minDist1;
}

glm::vec2 ProcGen::voronoiCenter(glm::vec2 corner) {
    float x = glm::fract(glm::sin(glm::dot(corner, glm::vec2(127.1, 311.7))) * 43758.5453);
    float z = glm::fract(glm::sin(glm::dot(corner, glm::vec2(420.2, 1337.1))) * 789221.1234);

    return glm::vec2(x, z);
}

float ProcGen::fbm2D(float x, float z, float persistence) {
    float total = 0;
    int octaves = 8;

    for (int i = 0; i < octaves; i++) {
        float frequency = pow(2, i);
        float amplitude = pow(persistence, i);

        total += perlinNoise2D(glm::vec2(x * frequency, z * frequency)) * amplitude;
    }

    return total;
}

float ProcGen::perlinNoise2D(glm::vec2 uv) {
    float surfletSum = 0.f;

    for (int dx = 0; dx <= 1; ++dx) {
        for (int dy = 0; dy <= 1; ++dy) {
            surfletSum += surflet(uv, glm::floor(uv) + glm::vec2(dx, dy));
        }
    }

    return surfletSum;
}

glm::vec2 pow(glm::vec2 v, int power) {
    for (int i = 0; i < power; i++) {
        v *= v;
    }

    return v;
}

float ProcGen::surflet(glm::vec2 p, glm::vec2 gridPoint) {
    glm::vec2 t2 = glm::abs(p - gridPoint);
    glm::vec2 t = glm::vec2(1.f) - 6.f * pow(t2, 5) + 15.f * pow(t2, 4) - 10.f * pow(t2, 3);

    glm::vec2 gradient = noise2DNormalVector(gridPoint) * 2.f - glm::vec2(1,1);
    glm::vec2 diff = p - gridPoint;

    float height = glm::dot(diff, gradient);

    return height * t.x * t.y;
}

glm::vec2 ProcGen::noise2DNormalVector(glm::vec2 v) {
    v += 0.01;
    glm::mat2 primes = glm::mat2{{126.1, 311.7}, {420.2, 1337.1}};

    return glm::normalize(glm::abs(glm::fract(glm::sin(primes * v))));
}

float ProcGen::linearInterp(float a, float b, float t) {
    return a * (1 - t) + b * t;
}

float ProcGen::cosineInterp(float a, float b, float t) {
    t = (1 - cos(t * PI)) * 0.5;

    return linearInterp(a, b, t);
}

float ProcGen::interpNoise2D(float x, float z) {
    float intX, fractX;
    fractX = modf(x, &intX);

    float intZ, fractZ;
    fractZ = modf(z, &intZ);

    float v1 = smoothNoise2D(intX, intZ);
    float v2 = smoothNoise2D(intX + 1, intZ);
    float v3 = smoothNoise2D(intX, intZ + 1);
    float v4 = smoothNoise2D(intX + 1, intZ + 1);

    float i1 = cosineInterp(v1, v2, fractX);
    float i2 = cosineInterp(v3, v4, fractX);

    return cosineInterp(i1, i2, fractZ);
}

float ProcGen::smoothNoise2D(float x, float z) {
    float corners = (noise2D(x - 1, z - 1) +
                     noise2D(x + 1, z - 1) +
                     noise2D(x - 1, z + 1) +
                     noise2D(x + 1, z + 1)) / 16;
    float sides = (noise2D(x - 1, z) +
                   noise2D(x + 1, z) +
                   noise2D(x, z - 1) +
                   noise2D(x, z + 1)) / 8;
    float center = noise2D(x, z) / 4;

    return corners + sides + center;
}

float ProcGen::noise2D(float x, float z) {
    float s = sin(glm::dot(glm::vec2(x, z), glm::vec2(127.1, 311.7))) * 43758.5453;

    return modf(s, nullptr);
}
