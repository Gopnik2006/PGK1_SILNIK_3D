#include "Obserwator.hpp"
#include <cmath>

Obserwator::Obserwator() {
    pos[0] = 0.0f; pos[1] = 0.0f; pos[2] = 5.0f;
    yaw = -90.0f;
    pitch = 0.0f;

    up[0] = 0.0f; up[1] = 1.0f; up[2] = 0.0f;

    updateVectors();
}

void Obserwator::apply() const {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        pos[0], pos[1], pos[2],
        pos[0] + front[0], pos[1] + front[1], pos[2] + front[2],
        up[0], up[1], up[2]
    );
}

void Obserwator::moveForward(float v) {
    pos[0] += front[0] * v;
    pos[1] += front[1] * v;
    pos[2] += front[2] * v;
}

void Obserwator::moveRight(float v) {
    GLfloat right[3] = {
        front[2], 0.0f, -front[0]
    };
    pos[0] += right[0] * v;
    pos[2] += right[2] * v;
}

void Obserwator::moveUp(float v) {
    pos[1] += v;
}

void Obserwator::rotate(float dx, float dy) {
    yaw += dx * sensitivity;
    pitch += dy * sensitivity;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateVectors();
}

void Obserwator::updateVectors() {
    float radYaw = yaw * 3.14159f / 180.0f;
    float radPitch = pitch * 3.14159f / 180.0f;

    front[0] = cos(radYaw) * cos(radPitch);
    front[1] = sin(radPitch);
    front[2] = sin(radYaw) * cos(radPitch);

    float len = sqrt(front[0] * front[0] + front[1] * front[1] + front[2] * front[2]);
    front[0] /= len; front[1] /= len; front[2] /= len;
}
