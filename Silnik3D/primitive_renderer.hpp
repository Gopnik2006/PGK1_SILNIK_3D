#pragma once
#include <GL/freeglut.h>

// Prosty renderer prymitywów korzystający z Vertex Arrays (stałe tablice)
class PrimitiveRenderer {
public:
    // Rysuje tablicę punktów (positions = [x,y,z,...], colors optional [r,g,b,...])
    static void drawPoints(const GLfloat* positions, int vertexCount,
        const GLfloat* colors = nullptr, int coordSize = 3) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(coordSize, GL_FLOAT, 0, positions);

        if (colors) {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(3, GL_FLOAT, 0, colors);
        }

        glDrawArrays(GL_POINTS, 0, vertexCount);

        if (colors) glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    // Rysuje linie / line strip / loops
    static void drawLines(const GLfloat* positions, int vertexCount, GLenum mode = GL_LINES,
        const GLfloat* colors = nullptr, int coordSize = 3) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(coordSize, GL_FLOAT, 0, positions);

        if (colors) {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(3, GL_FLOAT, 0, colors);
        }

        glDrawArrays(mode, 0, vertexCount);

        if (colors) glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    // Rysuje nieindeksowane trójkąty (glDrawArrays)
    static void drawTriangles(const GLfloat* positions, int vertexCount,
        const GLfloat* normals = nullptr,
        const GLfloat* colors = nullptr, int coordSize = 3) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(coordSize, GL_FLOAT, 0, positions);

        if (normals) {
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_FLOAT, 0, normals);
        }

        if (colors) {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(3, GL_FLOAT, 0, colors);
        }

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        if (colors) glDisableClientState(GL_COLOR_ARRAY);
        if (normals) glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
};
