#include "camera.h"

Camera::Camera()
    : forward(glm::vec4(0, 0, -1, 0)), right(glm::vec4(1, 0, 0, 0)),
      up(glm::vec4(0, 1, 0, 0)), fieldOfView(45),
      position(glm::vec4(0, 0, 10, 1)), nearClipPlane(0.01),
      farClipPlane(100.f), aspectRatio(1.f)
{}

glm::mat4 Camera::getViewMatrix() {
    glm::mat4 translateView(glm::vec4(1, 0, 0, 0),
                            glm::vec4(0, 1, 0, 0),
                            glm::vec4(0, 0, 1, 0),
                            glm::vec4(-glm::vec3(position), 1));

    glm::mat4 orientView(glm::vec4(right[0], up[0], forward[0], 0),
                         glm::vec4(right[1], up[1], forward[1], 0),
                         glm::vec4(right[2], up[2], forward[2], 0),
                         glm::vec4(0, 0, 0, 1));

    return orientView * translateView;
}

glm::mat4 Camera::getProjMatrix() {
    float p = farClipPlane / farClipPlane - nearClipPlane;
    float q = -farClipPlane * nearClipPlane / farClipPlane - nearClipPlane;
    float s = 1 / tan(fieldOfView / 2);

    return glm::mat4(glm::vec4(s / aspectRatio, 0, 0, 0),
                     glm::vec4(0, s, 0, 0),
                     glm::vec4(0, 0, p, 1),
                     glm::vec4(0, 0, q, 0));
}

void Camera::moveForward(float z) {
    glm::vec4 translate = forward * z;
    this->position += translate;
}

void Camera::moveRight(float x) {
    glm::vec4 translate = right * x;
    this->position += translate;
}

void Camera::moveUp(float y) {
    glm::vec4 translate = up * y;
    this->position += translate;
}

void Camera::rotateZ(float z) {
    glm::mat4 rotation = glm::rotate(glm::mat4(), z, glm::vec3(forward));
    right = rotation * right;
    up = rotation * up;
    forward = rotation * forward;
}

void Camera::rotateX(float x) {
    glm::mat4 rotation = glm::rotate(glm::mat4(), x, glm::vec3(right));
    right = rotation * right;
    up = rotation * up;
    forward = rotation * forward;
}

void Camera::rotateY(float y) {
    glm::mat4 rotation = glm::rotate(glm::mat4(), y, glm::vec3(up));
    right = rotation * right;
    up = rotation * up;
    forward = rotation * forward;
}
