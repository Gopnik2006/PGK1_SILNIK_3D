#include "Tetrahedron.hpp"

// --- WIERZCHOŁKI TETRAEDRU ---
// Prosty tetraedr o boku ~1
const GLfloat Tetrahedron::vertices[4][3] = {
    { 0.0f, 0.0f,  0.6f},   // 0 – czubek
    {-0.5f, -0.5f, 0.0f},   // 1 – podstawa
    { 0.5f, -0.5f, 0.0f},   // 2 – podstawa
    { 0.0f,  0.5f, 0.0f}    // 3 – podstawa
};

// --- NORMALNE DLA 4 TRÓJKĄTÓW ---
// Policzona ręcznie lub z cross-product
const GLfloat Tetrahedron::normals[4][3] = {
    { 0.0f, -0.5f,  0.8f},   // normal dla ściany (0,1,2)
    { 0.7f,  0.4f,  0.6f},   // normal dla ściany (0,2,3)
    {-0.7f,  0.4f,  0.6f},   // normal dla ściany (0,3,1)
    { 0.0f,  0.0f, -1.0f}    // normal dla podstawy (1,2,3)
};

// --- KOLORY WIERZCHOŁKÓW ---
const GLfloat Tetrahedron::colors[4][3] = {
    {1.0f, 0.0f, 0.0f},   // wierzcholek 0
    {0.0f, 1.0f, 0.0f},   // 1
    {0.0f, 0.0f, 1.0f},   // 2
    {1.0f, 1.0f, 0.0f}    // 3
};

// --- INDEKSY DLA 4 TRÓJKĄTÓW ---
const GLubyte Tetrahedron::indices[12] = {
    // ściana 1
    0, 1, 2,
    // ściana 2
    0, 2, 3,
    // ściana 3
    0, 3, 1,
    // podstawa
    1, 2, 3
};

void Tetrahedron::draw() const
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    // Rysujemy 4 trójkąty — każdy z własną normalną
    for (int face = 0; face < 4; ++face) {
        glNormal3fv(normals[face]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &indices[face * 3]);
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
