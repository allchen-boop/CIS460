#pragma once
#include "rotatenode.h"

RotateNode::RotateNode() : Node("rotate node")
{}

RotateNode::RotateNode(QString name, float angle)
    : Node(name), angle(angle)
{}

RotateNode::RotateNode(const RotateNode &node)
    : Node(node), angle(node.angle)
{}

glm::mat3 RotateNode::transform() {
    float rad = glm::radians(angle);
    return glm::mat3(cos(rad), sin(rad), 0,
                     -sin(rad),cos(rad), 0,
                     0, 0, 1);
}

void RotateNode::rotate(float angle) {
    this->angle = angle;
}

RotateNode::~RotateNode()
{}
