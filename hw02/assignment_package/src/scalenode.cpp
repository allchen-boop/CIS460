#pragma once
#include "scalenode.h"

ScaleNode::ScaleNode() : Node("scale node")
{}

ScaleNode::ScaleNode(QString name, float x, float y)
    :Node(name), x(x), y(y)
{}

ScaleNode::ScaleNode(const ScaleNode &node)
    : Node(node), x(node.x), y(node.y)
{}

float ScaleNode::getX() {
    glm::mat3 scale = transform();
    return scale[0][0];
}

float ScaleNode::getY() {
    glm::mat3 scale = transform();
    return scale[1][1];

}

void ScaleNode::scale(float x, float y) {
    this->x = x;
    this->y = y;
}

glm::mat3 ScaleNode::transform() {
    return glm::mat3(x, 0, 0,
                     0, y, 0,
                     0, 0, 1);
}

ScaleNode::~ScaleNode()
{}

