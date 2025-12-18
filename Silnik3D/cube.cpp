#include "cube.hpp"

Cube::Cube() {
    // Możesz zostawić pusty — konstruktor jest wymagany tylko po to,
    // aby istniała jego definicja (linker musi ją znaleźć).
}
// Wierzchołki sześcianu (unit cube centered at origin)
const GLfloat Cube::vertices[8][3] = {
    {-0.5f, -0.5f, -0.5f}, // 0
    { 0.5f, -0.5f, -0.5f}, // 1
    { 0.5f,  0.5f, -0.5f}, // 2
    {-0.5f,  0.5f, -0.5f}, // 3
    {-0.5f, -0.5f,  0.5f}, // 4
    { 0.5f, -0.5f,  0.5f}, // 5
    { 0.5f,  0.5f,  0.5f}, // 6
    {-0.5f,  0.5f,  0.5f}  // 7
};

// Normalne dla sześciu ścian (order: -Z, +Z, -X, +X, -Y, +Y) - można dopasować
const GLfloat Cube::normals[6][3] = {
    { 0.0f,  0.0f, -1.0f}, // back
    { 0.0f,  0.0f,  1.0f}, // front
    {-1.0f,  0.0f,  0.0f}, // left
    { 1.0f,  0.0f,  0.0f}, // right
    { 0.0f, -1.0f,  0.0f}, // bottom
    { 0.0f,  1.0f,  0.0f}  // top
};

// Proste kolory per-vertex
const GLfloat Cube::colors[8][3] = {
    {1.0f, 0.0f, 0.0f}, // 0 red
    {0.0f, 1.0f, 0.0f}, // 1 green
    {0.0f, 0.0f, 1.0f}, // 2 blue
    {1.0f, 1.0f, 0.0f}, // 3 yellow
    {1.0f, 0.0f, 1.0f}, // 4 magenta
    {0.0f, 1.0f, 1.0f}, // 5 cyan
    {1.0f, 1.0f, 1.0f}, // 6 white
    {0.2f, 0.2f, 0.2f}  // 7 dark
};

// Indeksy: 12 trójkątów (2 per face) -> 36 elementów
// Każdy trójkąt to 3 indeksy do tablicy vertices
const GLubyte Cube::indices[36] = {
    // back face (-Z): 0,1,2, 2,3,0
    0,1,2,  2,3,0,
    // front face (+Z): 5,4,7, 7,6,5  (note winding to have consistent normals)
    5,4,7,  7,6,5,
    // left face (-X): 4,0,3, 3,7,4
    4,0,3,  3,7,4,
    // right face (+X): 1,5,6, 6,2,1
    1,5,6,  6,2,1,
    // bottom (-Y): 4,5,1, 1,0,4
    4,5,1,  1,0,4,
    // top (+Y): 3,2,6, 6,7,3
    3,2,6,  6,7,3
};

void Cube::draw() const {
    // Aktywuj tablice
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0][0]);

    // Ustaw normalne (tu: prosta per-face normal nie per-vertex; jednak
    // glNormalPointer przyjmuje per-vertex. Zrobimy prosty trick: powtórzymy
    // normalne per-wierzchołek używając tablicy zbudowanej dynamicznie albo
    // użyjemy OpenGL immediate style przy nakładaniu normalnych - prostsze:
    // ustawiamy material / normal przed rysowaniem każdego trójkąta.
    // Jednak aby trzymać się zadania: pokażę użycie glDrawElements z color array.
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, &colors[0][0]);

    // Wersja: rysujemy po trójkątach i ustawiamy normal per-face (glNormal3f)
    // — to wymaga pętli i glDrawElements dla podzbioru. Dla prostoty: rozbijemy
    // draw na 6 ścian i wywołamy glDrawElements dla każdego kawałka.
    const GLubyte* idx = indices;
    for (int face = 0; face < 6; ++face) {
        // każdy face ma 2 trójkąty = 6 indeksów
        glNormal3fv(normals[face]);         // normal per-face
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, idx + face * 6);
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
