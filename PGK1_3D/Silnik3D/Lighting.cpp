#include "Lighting.hpp"

// Stan oświetlenia
bool Lighting::enabled = true;
ShadeMode Lighting::shadeMode = PHONG_FIXED;

void Lighting::init() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    // Ambient
    GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    // Diffuse
    GLfloat diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    // Specular
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    // Pozycja światła
    GLfloat position[] = { -5.0f, 5.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    // Material (specular + shininess)
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 50.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void Lighting::apply() {
    if (enabled) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        switch (shadeMode) {
        case FLAT:
            glShadeModel(GL_FLAT);
            break;
        case GOURAUD:
            glShadeModel(GL_SMOOTH);
            break;
        case PHONG_FIXED:
            glShadeModel(GL_SMOOTH); // w Fixed-Function Pipeline Phong = smooth
            break;
        }
    }
    else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }
}

void Lighting::toggleLight() {
    enabled = !enabled;
}

void Lighting::setShadeMode(ShadeMode mode) {
    shadeMode = mode;
}
