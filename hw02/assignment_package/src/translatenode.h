#ifndef TRANSLATENODE_H
#define TRANSLATENODE_H
#include <node.h>

class TranslateNode : public Node
{

protected:
    float x;
    float y;

public:
    TranslateNode();
    TranslateNode(float x, float y, QString name);
    TranslateNode(const TranslateNode &node);

    float getX();
    float getY();
    void translate(float x, float y);
    glm::mat3 transform();
    virtual ~TranslateNode();
};

#endif // TRANSLATENODE_H
