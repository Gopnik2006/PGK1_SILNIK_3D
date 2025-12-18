#pragma once
#include <GL/freeglut.h>

class Obserwator {
public:
    Obserwator();

    // wywoływane co klatkę PRZED rysowaniem
    void apply() const;

    // ruch
    void moveForward(float v);
    void moveRight(float v);
    void moveUp(float v);

    // obrót (mysz)
    void rotate(float dx, float dy);

private:
    GLfloat pos[3];
    GLfloat front[3];
    GLfloat up[3];

    float yaw;
    float pitch;
    float speed = 5.0f;
    float sensitivity = 0.1f;

    void updateVectors();
};
