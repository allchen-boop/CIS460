#include "linesegment.h"

LineSegment::LineSegment(glm::vec2 endPt1, glm::vec2 endPt2)
    : dx(endPt2[0] - endPt1[0]), dy(endPt2[1] - endPt1[1]),
      endPt1(endPt1), endPt2(endPt2)
{}


bool LineSegment::getIntersection(int y, float* x) {
    float max = std::max(endPt1[1], endPt2[1]);
    float min = std::min(endPt1[1], endPt2[1]);

    if (y <= max) {
        if (y >= min) {

            if (dy == 0 || dx == 0) {
                *x = endPt1[0];
                return true;
            }

            float slope = dy / dx;
            float intersection = y + (endPt1[0] * slope) - endPt1[1];

            intersection = intersection / slope;
            glm::clamp(intersection, 0.f, 512.f);

            *x = intersection;
            return true;
        }
    }
    return false;
}
