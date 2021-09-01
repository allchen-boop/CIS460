#pragma once

#include <glm_includes.h>

class ProcGen {
public:
    ProcGen();
    ~ProcGen();

    static int getHeight(int x, int z);

private:
    static float grasslands(float x, float z);
    static float mountains(float x, float z);

    static float worleyNoise(float x, float z);
    static glm::vec2 voronoiCenter(glm::vec2);

    static float fbm2D(float x, float z, float persistence);
    static float perlinNoise2D(glm::vec2);
    static float surflet(glm::vec2, glm::vec2);
    static glm::vec2 noise2DNormalVector(glm::vec2);

    static float interpNoise2D(float x, float z);
    static float smoothNoise2D(float x, float z);
    static float noise2D(float x, float z);

    static float cosineInterp(float a, float b, float t);
    static float linearInterp(float a, float b, float t);
};
