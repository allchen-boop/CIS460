#ifndef SCALENODE_H
#define SCALENODE_H

#include <node.h>

class ScaleNode : public Node
{

private:
    float x;
    float y;

public:
    ScaleNode();
    ScaleNode(QString name, float x, float y);
    ScaleNode(const ScaleNode &node);

    float getX();
    float getY();

    void scale(float x, float y);
    glm::mat3 transform();
    virtual ~ScaleNode();
};

#endif // SCALENODE_H
