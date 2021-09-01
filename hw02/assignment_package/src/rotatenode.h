#ifndef ROTATENODE_H
#define ROTATENODE_H

#include <node.h>

class RotateNode : public Node
{

private:
    float angle;

public:
    RotateNode();
    RotateNode(QString name, float angle);
    RotateNode(const RotateNode &node);

    glm::mat3 transform();
    void rotate(float angle);
    virtual ~RotateNode();
};

#endif // ROTATENODE_H
