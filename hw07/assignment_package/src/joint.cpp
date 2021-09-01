#include "joint.h"

int Joint::lastJoint = 0;

Joint::Joint()
    : QTreeWidgetItem(),
      name(), parent(nullptr), children(),
      pos(glm::vec4()),
      rot(glm::quat()),
      bind_matrix(glm::mat4()),
      id(lastJoint++)
{
    this->QTreeWidgetItem::setText(0, this->name);
}

Joint::Joint(QString name)
    : QTreeWidgetItem(),
      name(name), parent(nullptr), children(),
      pos(glm::vec4()),
      rot(glm::quat()),
      bind_matrix(glm::mat4()),
      id(lastJoint++)
{
    this->QTreeWidgetItem::setText(0, this->name);
}

glm::mat4 Joint::getLocalTransformation() {
    glm::mat4 t = glm::mat4(glm::vec4(1, 0, 0, 0),
                            glm::vec4(0, 1, 0, 0),
                            glm::vec4(0, 0, 1, 0),
                            glm::vec4(pos, 1));

    glm::mat4 r = glm::mat4_cast(rot);

    return t * r;
}

glm::mat4 Joint::getOverallTransformation() {
    if (parent) {
        return parent->getOverallTransformation() *
                getLocalTransformation();
    }
    return getLocalTransformation();
}

void Joint::addChild(Joint *child) {
    QTreeWidgetItem::addChild(child);
    children.push_back(child);
    child->parent = this;
}
