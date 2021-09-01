#ifndef LINE_H
#define LINE_H

#include <polygon.h>

class LineSegment
{
public:
    float dx;
    float dy;

    // segment's endpoints
    glm::vec2 endPt1;
    glm::vec2 endPt2;

    LineSegment(glm::vec2 endPt1, glm::vec2 endPt2);

    bool getIntersection(int y, float* x);
};

#endif // LINE_H
