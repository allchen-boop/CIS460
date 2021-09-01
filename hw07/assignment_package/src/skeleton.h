#ifndef SKELETON_H
#define SKELETON_H

#include <joint.h>
#include <drawable.h>
#include <smartpointerhelp.h>

class Skeleton : public Drawable
{

public: 
    std::vector<uPtr<Joint>> joints;

    int representedJoint;

    // Creates VBO data to make a visual
    // representation of the currently selected Joint
    void create() override;
    // Change which Joint representedJoint points to
    void updateJoint(Joint*);
    std::vector<glm::mat4> setTranslateMatrix();
    void setBindMatrix();

    GLenum drawMode() override;

    Skeleton(OpenGLContext* context);

    ~Skeleton();
};

#endif // SKELETON_H
