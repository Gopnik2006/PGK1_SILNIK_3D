#include "custom_object.hpp"

void CustomObject::draw() const {
    // proste wierzchołki dla litery L (nieindeksowane)
    static const GLfloat verts[] = {
        // pierwszy quad (pion)
        -0.1f, -0.5f, 0.0f,
         0.1f, -0.5f, 0.0f,
         0.1f,  0.5f, 0.0f,
        -0.1f,  0.5f, 0.0f,
        // drugi quad (dolny poziomy)
        -0.5f, -0.5f, 0.0f,
         0.3f, -0.5f, 0.0f,
         0.3f, -0.3f, 0.0f,
        -0.5f, -0.3f, 0.0f
    };
    static const GLfloat cols[] = {
        1,0,0,  1,0,0,  1,0,0,  1,0,0,
        0,1,0,  0,1,0,  0,1,0,  0,1,0
    };

    // rysuj jako dwa TRIANGLE_FAN (po 4 wierzchołki każdy)
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, verts);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, cols);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
