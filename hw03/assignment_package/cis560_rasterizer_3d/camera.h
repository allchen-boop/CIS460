#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{

public:
    glm::vec4 forward;      // z axis
    glm::vec4 right;        // x axis
    glm::vec4 up;           // y axis
    float fieldOfView;      // field of view
    glm::vec4 position;     // camera's position in world space
    float nearClipPlane;    // camera's near clip plane
    float farClipPlane;     // camera's far clip plane
    float aspectRatio;      // aspect ratio

    Camera();

    glm::mat4 getViewMatrix();
    glm::mat4 getProjMatrix();

    void moveForward(float z);
    void moveRight(float x);
    void moveUp(float y);

    void rotateZ(float z);
    void rotateX(float x);
    void rotateY(float y);
};

#endif
