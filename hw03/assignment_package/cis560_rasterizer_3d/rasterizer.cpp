#include "rasterizer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <linesegment.h>

Rasterizer::Rasterizer(const std::vector<Polygon>& polygons)
    : m_polygons(polygons), cam(Camera())
{}

// area helper
float area(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
    glm::vec3 cross = glm::cross(p1 - p2, p3 - p2);
    float area = 0.5 * glm::length(cross);
    return area;
}

// barycentric interpolation weight helper
glm::vec3 baryWeight(Vertex v1, Vertex v2, Vertex v3, glm::vec3 p) {

    glm::vec3 p1 = glm::vec3(v1.m_posc[0], v1.m_posc[1], 0);
    glm::vec3 p2 = glm::vec3(v2.m_posc[0], v2.m_posc[1], 0);
    glm::vec3 p3 = glm::vec3(v3.m_posc[0], v3.m_posc[1], 0);

    float s = area(p1, p2, p3);
    float s1 = area(p, p2, p3);
    float s2 = area(p, p3, p1);
    float s3 = area(p, p1, p2);

    float z1 = v1.m_posc[2];
    float z2 = v2.m_posc[2];
    float z3 = v3.m_posc[2];

    glm::vec3 baryWeight = glm::vec3(s1 / (z1 * s), s2 / (z2 * s), s3 / (z3 * s));

    return baryWeight;
}

glm::vec4 Rasterizer::interpolate_normal(Vertex v1, Vertex v2, Vertex v3, glm::vec3 p, float z) {

    glm::vec4 p1_norm = v1.m_normal;
    glm::vec4 p2_norm = v2.m_normal;
    glm::vec4 p3_norm = v3.m_normal;

    float c1 = baryWeight(v1, v2, v3, p)[0];
    float c2 = baryWeight(v1, v2, v3, p)[1];
    float c3 = baryWeight(v1, v2, v3, p)[2];

    return z * (p1_norm * c1 + p2_norm * c2 + p3_norm * c3);
}

glm::vec2 Rasterizer::interpolate_uv(Vertex v1, Vertex v2, Vertex v3, glm::vec3 p, float z) {

    glm::vec2 p1_uv = v1.m_uv;
    glm::vec2 p2_uv = v2.m_uv;
    glm::vec2 p3_uv = v3.m_uv;

    float c1 = baryWeight(v1, v2, v3, p)[0];
    float c2 = baryWeight(v1, v2, v3, p)[1];
    float c3 = baryWeight(v1, v2, v3, p)[2];

    return z * (p1_uv * c1 + p2_uv * c2 + p3_uv * c3);
}

float Rasterizer::interpolate_z(Vertex v1, Vertex v2, Vertex v3, glm::vec3 p) {

    float c1 = baryWeight(v1, v2, v3, p)[0];
    float c2 = baryWeight(v1, v2, v3, p)[1];
    float c3 = baryWeight(v1, v2, v3, p)[2];

    return 1 / (c1 + c2 + c3);
}

QImage Rasterizer::RenderScene()
{
    QImage result(512, 512, QImage::Format_RGB32);
    // Fill the image with black pixels.
    // Note that qRgb creates a QColor,
    // and takes in values [0, 255] rather than [0, 1].
    result.fill(qRgb(0.f, 0.f, 0.f));

    std::vector<float> zBuffer(512 * 512, std::numeric_limits<float>::max());

    for (Polygon &p : m_polygons) {

        // projection from world space to pixel space
        for (Vertex &v : p.m_verts) {
             v.m_posc = cam.getProjMatrix() * cam.getViewMatrix() * v.m_pos;
             v.m_posc =  v.m_posc / v.m_posc[3];
             v.m_posc[0] = (v.m_posc[0] + 1) * result.width() / 2;
             v.m_posc[1] = (1 - v.m_posc[1]) * result.height() / 2;
        }

        for (Triangle &t : p.m_tris) {

            Vertex v1 = p.m_verts[t.m_indices[0]];
            Vertex v2 = p.m_verts[t.m_indices[1]];
            Vertex v3 = p.m_verts[t.m_indices[2]];

            glm::vec4 vert1 = v1.m_posc;
            glm::vec4 vert2 = v2.m_posc;
            glm::vec4 vert3 = v3.m_posc;

            LineSegment line1 = LineSegment(glm::vec2(vert1[0], vert1[1]),
                                            glm::vec2(vert2[0], vert2[1]));
            LineSegment line2 = LineSegment(glm::vec2(vert2[0], vert2[1]),
                                            glm::vec2(vert3[0], vert3[1]));
            LineSegment line3 = LineSegment(glm::vec2(vert1[0], vert1[1]),
                                            glm::vec2(vert3[0], vert3[1]));
            LineSegment lines[3] = {line1, line2, line3};

            // bounding box
            float left = std::min(std::min(v1.m_posc[0], v2.m_posc[0]), v3.m_posc[0]);
            float right = std::max(std::max(v1.m_posc[0], v2.m_posc[0]), v3.m_posc[0]);
            float top = std::min(std::min(v1.m_posc[1], v2.m_posc[1]), v3.m_posc[1]);
            float bottom = std::max(std::max(v1.m_posc[1], v2.m_posc[1]), v3.m_posc[1]);

            float yStart = glm::clamp(top, 0.f, 512.f);
            float yEnd = glm::clamp(bottom, 0.f, 512.f);

            float y = ceil(yStart);
            while (y < yEnd) {

                // pseudo code from write up
                float xLeft = 512.f;
                float xRight = 0.f;

                for (LineSegment& LineSegment : lines) {
                    float x = 0.f;
                    if (LineSegment.getIntersection(y, &x)) {
                        xLeft = std::min(xLeft, x);
                        xRight = std::max(xRight, x);
                    }
                }

                xLeft = glm::clamp(xLeft, 0.f, 512.f);
                xRight = glm::clamp(xRight, 0.f, 512.f);

                float x = ceil(xLeft);
                while (x < xRight) {

                    float z = interpolate_z(v1, v2, v3, glm::vec3(x, y, 0));

                    if (z < zBuffer[512 * x + y]) {
                        zBuffer[512 * x + y] = z;

                        glm::vec2 uv = interpolate_uv(v1, v2, v3, glm::vec3(x, y, 0), z);
                        glm::vec4 normal = interpolate_normal(v1, v2, v3, glm::vec3(x, y, 0), z);

                        glm::vec4 n = glm::normalize(normal);
                        glm::vec4 l = glm::normalize(-cam.forward);

                        // lambertian
                        float light = glm::clamp(glm::dot(n, l), 0.f, 1.f);
                        glm::vec3 texture = GetImageColor(uv, p.mp_texture);

                        glm::vec3 color = light * texture;
                        result.setPixel(x, y, qRgb(color[0], color[1], color[2]));
                    }
                    x++;
                }
                y++;
            }
        }
    }
     return result;
}

void Rasterizer::ClearScene()
{
    m_polygons.clear();
}
