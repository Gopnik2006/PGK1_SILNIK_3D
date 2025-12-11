#pragma once
#include <GL/freeglut.h>

class Kula {
public:
    Kula();
    ~Kula() = default;

    // Rysuje sześcian. Przy wywołaniu setup GL powinien mieć odpowiednie macierze.
    void draw() const;

private:
    static const GLfloat vertices[18][3];
    static const GLfloat normals[32][3];
    static const GLfloat colors[18][3];
    // Indeksy dla 12 trójkątów (36 indeksów) - 2 trójkąty na ścianę
    static const GLubyte indices[96];
};