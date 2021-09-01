#ifndef JOINT_H
#define JOINT_H

#include <la.h>
#include <QTreeWidget>

class Joint : public QTreeWidgetItem
{
public:
    static int lastJoint;

    QString name;                   // name which will be displayed in QTreeWidget of joints
    Joint* parent;                  // the joint that is the parent of this joint
    std::vector<Joint*> children;   // set of joints that have this joint as their parent
    glm::vec3 pos;                  // position of this joint relative to its parent joint
    glm::quat rot;                  // quaternion that represents this joint's current orientation
    glm::mat4 bind_matrix;          // inverse of the joint's compound transformation matrix at the time a mesh is bound to the joint's skeleton
    int id;

    glm::mat4 getLocalTransformation();
    glm::mat4 getOverallTransformation();

    void addChild(Joint *child);

    Joint();
    Joint(QString name);
};

#endif // JOINT_H
