#pragma once
#include <GL/freeglut.h>

// Tetrahedron: piramida o 4 wierzchołkach, 4 trójkątach.
// Indeksowana jak Cube, rysowana glDrawElements.
class Tetrahedron {
public:
    Tetrahedron() = default;
    ~Tetrahedron() = default;

    void draw() const;

private:
    static const GLfloat vertices[4][3];
    static const GLfloat normals[4][3];
    static const GLfloat colors[4][3];
    static const GLubyte indices[12]; // 4 trójkąty * 3 indeksy
};