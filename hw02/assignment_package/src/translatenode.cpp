#include "translatenode.h"

TranslateNode::TranslateNode() : Node("translate node")
{}

TranslateNode::TranslateNode(float x, float y, QString name)
    : Node(name), x(x), y(y)
{}

TranslateNode::TranslateNode(const TranslateNode &node)
    : Node(node), x(node.x), y(node.y)
{}

float TranslateNode::getX() {
    glm::mat3 translate = transform();
    return translate[2][0];
}

float TranslateNode::getY() {
    glm::mat3 translate = transform();
    return translate[2][1];
}

void TranslateNode::translate(float x, float y) {
    this->x = x;
    this->y = y;
}

glm::mat3 TranslateNode::transform() {
    return glm::mat3(1, 0, 0,
                     0, 1, 0,
                     x, y, 1);
}

TranslateNode::~TranslateNode()
{}
