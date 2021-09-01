#pragma once
#include <polygon.h>
#include <linesegment.h>
#include <QImage>
#include "camera.h"

class Rasterizer
{
private:
    //This is the set of Polygons loaded from a JSON scene file
    std::vector<Polygon> m_polygons;

public:
    Rasterizer(const std::vector<Polygon>& polygons);
    QImage RenderScene();
    void ClearScene();

    Camera cam;
    float interpolate_z(Vertex v1, Vertex v2, Vertex v3, glm::vec3 p);
    glm::vec2 interpolate_uv(Vertex v1, Vertex v2, Vertex v3, glm::vec3 p, float z);
    glm::vec4 interpolate_normal(Vertex v1, Vertex v2, Vertex v3, glm::vec3 p, float z);
};
