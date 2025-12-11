#include "kula.hpp"

Kula::Kula() {
    // Możesz zostawić pusty — konstruktor jest wymagany tylko po to,
    // aby istniała jego definicja (linker musi ją znaleźć).
}
// Wierzchołki 
const GLfloat Kula::vertices[18][3] = {
    { 0.0f,  1.0f,  0.0f},    // 0 gora                       
    { 0.0f, -1.0f,  0.0f},    // 1 dol
    { 0.0f,  0.0f, -1.0f},    // 2 back
    { 0.0f,  0.0f,  1.0f},    // 3 front
    {-1.0f,  0.0f,  0.0f},    // 4 left
    { 1.0f,  0.0f,  0.0f},    // 5 right
    { 0.71f,  0.0f, -0.71f},  // 6 b-r
    {-0.71f,  0.0f, -0.71f},  // 7 b-l
    {-0.71f,  0.0f,  0.71f},  // 8 f-l
    { 0.71f,  0.0f,  0.71f},  // 9 f-r
    { 0.58f,  0.58f, -0.58f}, // 10 g b-r
    {-0.58f,  0.58f, -0.58f}, // 11 g b-l
    { 0.58f,  0.58f,  0.58f}, // 12 g f-r
    {-0.58f,  0.58f,  0.58f}, // 13 g f-l
    { 0.58f, -0.58f, -0.58f}, // 14 d b-r
    {-0.58f, -0.58f, -0.58f}, // 15 d b-l
    { 0.58f, -0.58f,  0.58f}, // 16 d f-r
    {-0.58f, -0.58f,  0.58f}  // 17 d f-l
};

const GLfloat Kula::normals[32][3] = {
    {  0.000000f,  0.809942f, -0.586510f },
    {  0.000000f,  0.809942f,  0.586510f },
    { -0.707107f,  0.000000f,  0.707107f },
    { -0.707107f,  0.000000f, -0.707107f },

    {  0.000000f, -0.809942f, -0.586510f },
    {  0.000000f, -0.809942f,  0.586510f },
    {  0.707107f,  0.000000f,  0.707107f },
    {  0.707107f,  0.000000f, -0.707107f },

    { -0.362943f,  0.280515f,  0.888585f },
    {  0.362943f, -0.280515f,  0.888585f },
    {  0.362943f,  0.280515f,  0.888585f },
    { -0.362943f, -0.280515f,  0.888585f },

    {  0.000000f,  0.586510f,  0.809942f },
    {  0.000000f, -0.586510f,  0.809942f },
    { -0.362943f,  0.280515f,  0.888585f },
    {  0.362943f, -0.280515f, -0.888585f },

    { -0.362943f,  0.280515f, -0.888585f },
    { -0.362943f, -0.280515f, -0.888585f },
    {  0.362943f,  0.280515f, -0.888585f },
    {  0.362943f, -0.280515f,  0.888585f },

    { -0.888585f,  0.280515f, -0.362943f },
    { -0.888585f, -0.280515f, -0.362943f },
    { -0.888585f,  0.280515f,  0.362943f },
    { -0.888585f, -0.280515f,  0.362943f },

    {  0.809942f, -0.586510f,  0.000000f },
    { -0.809942f, -0.586510f,  0.000000f },

    {  0.888585f,  0.280515f, -0.362943f },
    {  0.888585f, -0.280515f, -0.362943f },
    {  0.888585f,  0.280515f,  0.362943f },
    {  0.888585f, -0.280515f,  0.362943f },

    {  0.809942f,  0.586510f,  0.000000f },
    { -0.809942f,  0.586510f, -0.000000f }
};


// Proste kolory per-vertex
const GLfloat Kula::colors[18][3] = {
    {1.0f, 0.5f, 0.9f}, // 0 red
    {1.0f, 0.0f, 0.9f}, // 0 red
    {2.0f, 0.9f, 0.8f}, // 0 red
    {2.0f, 0.0f, 0.8f}, // 0 red
    {3.0f, 0.7f, 0.7f}, // 0 red
    {3.0f, 0.0f, 0.7f}, // 0 red
    {4.0f, 0.8f, 0.6f}, // 0 red
    {4.0f, 0.0f, 0.6f}, // 0 red
    {5.0f, 0.2f, 0.5f}, // 0 red
    {5.0f, 0.0f, 0.5f}, // 0 red
    {6.0f, 0.1f, 0.4f}, // 0 red
    {6.0f, 0.0f, 0.4f}, // 0 red
    {7.0f, 0.4f, 0.3f}, // 0 red
    {7.0f, 0.0f, 0.3f}, // 0 red
    {8.0f, 0.6f, 0.2f}, // 0 red
    {8.0f, 0.0f, 0.2f}, // 0 red
    {9.0f, 0.3f, 0.1f}, // 0 red
    {9.0f, 0.0f, 0.1f}, // 0 red
};


// Każdy trójkąt to 3 indeksy do tablicy vertices
const GLubyte Kula::indices[96] = {
    // gora 12 (4)
    0,10,11,  0,10,12,  0,12,13,  0,13,11,
    // dol 12 (4)
    1,14,15,  1,14,16,  1,16,17,  1,17,15,
    // front 18 (6)
    3,8,13,  3,8,17,  3,9,12,  3,9,16,  3,12,13,  3,16,17,
    // back 18 (6)
    2,6,10,  2,6,14,  2,7,11,  2,7,15,  2,10,11,  2,14,15,
    // left 18 (6)
    4,7,11,  4,7,15,  4,8,13,  4,8,17,  4,11,13,  4,15,17,
    // right 18 (6)
    5,6,10,  5,6,14,  5,9,12,  5,9,16,  5,10,12,  5,14,16
};

void Kula::draw() const {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vertices[0][0]);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, &colors[0][0]);

    // Mamy 32 trójkąty → każdy po 3 indeksy
    for (int i = 0; i < 32; i++) {
        glNormal3fv(normals[i]);         // normalna dla i-tego trójkąta
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &indices[i * 3]);
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}