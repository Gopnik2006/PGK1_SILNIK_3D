#pragma once
#include <GL/freeglut.h>

// Klasa Cube: indeksowany sześcian z wierzchołkami, normalami i kolorami.
// Używa glDrawElements.
class Cube {
public:
    Cube();
    ~Cube() = default;

    // Rysuje sześcian. Przy wywołaniu setup GL powinien mieć odpowiednie macierze.
    void draw() const;

private:
    static const GLfloat vertices[8][3];
    static const GLfloat normals[6][3];
    static const GLfloat colors[8][3];
    // Indeksy dla 12 trójkątów (36 indeksów) - 2 trójkąty na ścianę
    static const GLubyte indices[36];
};
