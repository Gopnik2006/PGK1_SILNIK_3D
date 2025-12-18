#include "Engine.hpp"
#include "cube.hpp"
#include "kula.hpp"
#include "tetrahedron.hpp"
#include "Obserwator.hpp"

// Obiekty sceny
Cube cube;
Kula kula;
Tetrahedron tetr;

// Kamera
Obserwator obserwator;

int lastMouseX = 0;
int lastMouseY = 0;
bool firstMouse = true;

int main(int argc, char** argv) {
    Engine::Config cfg;
    cfg.width = 1920;
    cfg.height = 1080;
    cfg.fullscreen = true;
    cfg.doubleBuffer = true;
    cfg.depthBuffer = true;
    cfg.targetFPS = 60;
    cfg.projection = ProjectionMode::PERSPECTIVE;
    cfg.fov = 70.0f;

    Engine engine(cfg);

    /*
    glEnable(GL_LIGHTING);
    GLfloat amb[] = { 1.0, 1.0, 1.0, 10.0 }; // RGBA
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
    GLfloat diff[] = { 1.0, 1.0, 1.0, 1.0 }; // RGBA
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    GLfloat spec[] = { 1.0, 1.0, 1.0, 1.0 }; // RGBA
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    GLfloat pos[] = { 00.0, 10.0, 00.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.0);
    */

    // ================= RENDER =================
    engine.setRenderCallback([&]() {

        // >>> KAMERA <<<
        obserwator.apply();

        // -------- CUBE --------
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef((float)glutGet(GLUT_ELAPSED_TIME) * 0.02f,
            0.0f, 0.0f, 1.0f);
        cube.draw();
        glPopMatrix();

        // -------- KULA --------
        glPushMatrix();
        glTranslatef(3.0f, 0.0f, 0.0f);
        glRotatef((float)glutGet(GLUT_ELAPSED_TIME) * 0.02f,
            1.0f, 0.0f, 0.0f);
        kula.draw();
        glPopMatrix();

        // -------- TETRAHEDRON --------
        glPushMatrix();
        glTranslatef(-3.0f, 0.0f, 0.0f);
        glRotatef((float)glutGet(GLUT_ELAPSED_TIME) * 0.02f,
            0.0f, 1.0f, 0.0f);
        tetr.draw();
        glPopMatrix();
        });

    // ================= UPDATE =================
    engine.setUpdateCallback([&](double dt) {

        float speed = 5.0f * (float)dt;
        float rotSpeed = 180.0f * (float)dt;

        // ruch
        if (GetAsyncKeyState('W') & 0x8000) obserwator.moveForward(speed);
        if (GetAsyncKeyState('S') & 0x8000) obserwator.moveForward(-speed);
        if (GetAsyncKeyState('A') & 0x8000) obserwator.moveRight(speed);
        if (GetAsyncKeyState('D') & 0x8000) obserwator.moveRight(-speed);
        if (GetAsyncKeyState('Q') & 0x8000) obserwator.moveUp(speed);
        if (GetAsyncKeyState('E') & 0x8000) obserwator.moveUp(-speed);

        // obrót – strzałki
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) obserwator.rotate(rotSpeed, 0);
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) obserwator.rotate(-rotSpeed, 0);
        if (GetAsyncKeyState(VK_UP) & 0x8000) obserwator.rotate(0, -rotSpeed);
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) obserwator.rotate(0, rotSpeed);
        
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            obserwator.rotate(rotSpeed, 0);
            obserwator.moveRight(speed/2.5);
        };
        if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
            obserwator.rotate(-rotSpeed, 0);
            obserwator.moveRight(-speed/2.5);
        };
     });

    engine.init(argc, argv);
    engine.start();

    return 0;
}
