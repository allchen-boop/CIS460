#include <skeleton.h>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

Skeleton::Skeleton(OpenGLContext *context)
    : Drawable(context), representedJoint(-1) {}

Skeleton::~Skeleton() {}

void Skeleton::create() {
    std::vector<glm::vec4> pos;
    std::vector<glm::vec4> col;
    std::vector<GLuint> idx;

    int start = 0;
    int n = 0;
    for (uPtr<Joint> &joint : joints) {

        // x axis
        glm::vec4 offset = glm::vec4(0, 0.5, 0, 1);
        glm::vec3 axis = glm::vec3(1, 0, 0);
        start = n;

        for (int i = 0; i < 12; i++) {
            pos.push_back(joint->getOverallTransformation() * offset);

            if (joint->id == representedJoint) {
                col.push_back(glm::vec4(1, 1, 1, 1));
            } else {
                col.push_back(glm::vec4(1, 0, 0, 1));
            }

            idx.push_back(n);
            if (i == 11) {
                idx.push_back(start);
            } else {
                idx.push_back(n + 1);
            }
            offset = glm::rotate(offset, glm::radians(30.f), axis);
            n++;
        }

        offset = glm::vec4(0, 0, 0.5, 1);
        axis = glm::vec3(0, 1, 0);
        start = n;

        for (int i = 0; i < 12; i++) {
            pos.push_back(joint->getOverallTransformation() * offset);

            if (joint->id == representedJoint) {
                 col.push_back(glm::vec4(1, 1, 1, 1));
            } else {
                col.push_back(glm::vec4(0, 1, 0, 1));
            }

            idx.push_back(n);
            if (i == 11) {
                idx.push_back(start);
            } else {
                idx.push_back(n + 1);
            }
            offset = glm::rotate(offset, glm::radians(30.f), axis);
            n++;
        }

        offset = glm::vec4(0.5, 0, 0, 1);
        axis = glm::vec3(0, 0, 1);
        start = n;

        for (int i = 0; i < 12; i++) {
            pos.push_back(joint->getOverallTransformation() * offset);

            if (joint->id == representedJoint) {
                 col.push_back(glm::vec4(1, 1, 1, 1));
            } else {
                col.push_back(glm::vec4(0, 0, 1, 1));
            }

            idx.push_back(n);
            if (i == 11) {
                idx.push_back(start);
            } else {
                idx.push_back(n + 1);
            }
            offset = glm::rotate(offset, glm::radians(30.f), axis);
            n++;
        }

        if (joint->parent) {
            pos.push_back(joint->getOverallTransformation() * glm::vec4(0, 0, 0, 1));
            pos.push_back(joint->parent->getOverallTransformation() * glm::vec4(0, 0, 0, 1));
            col.push_back(glm::vec4(1, 1, 0, 1));
            col.push_back(glm::vec4(1, 0, 1, 1));
            idx.push_back(n);
            idx.push_back(++n);
            n++;
        }
    }

    count = idx.size();

    generateIdx();
    bindIdx();
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

    generatePos();
    bindPos();
    mp_context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

    generateCol();
    bindCol();
    mp_context->glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(glm::vec4), col.data(), GL_STATIC_DRAW);
}

GLenum Skeleton::drawMode() {
    return GL_LINES;
}

void Skeleton::updateJoint(Joint* joint) {
    representedJoint = joint->id;
}

std::vector<glm::mat4> Skeleton::setTranslateMatrix() {
    std::vector<glm::mat4> trans;
    for (uPtr<Joint> &j : joints) {
        trans.push_back(j->getOverallTransformation());
    }
    return trans;

}
void Skeleton::setBindMatrix() {
    for (uPtr<Joint> &j : joints) {
        j->bind_matrix = glm::inverse(j->getOverallTransformation());
    }
}
