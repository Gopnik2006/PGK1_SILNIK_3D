#pragma once
#include <GL/freeglut.h>

// Klasa Cube: indeksowany sześcian z wierzchołkami, normalami i kolorami.
// Używa glDrawElements.
class Floor {
public:
    Floor();
    ~Floor() = default;

    // Rysuje sześcian. Przy wywołaniu setup GL powinien mieć odpowiednie macierze.
    void draw() const;

private:
    static const GLfloat vertices[81][3];
    static const GLfloat normals[1][3];
    static const GLfloat colors[1][3];
    // Indeksy dla 12 trójkątów (36 indeksów) - 2 trójkąty na ścianę
    static const GLubyte indices[128];
};
