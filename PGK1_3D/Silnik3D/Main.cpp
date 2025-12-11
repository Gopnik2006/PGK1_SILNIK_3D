#include "Engine.hpp"
#include "cube.hpp"
#include "custom_object.hpp"
#include "kula.hpp"
#include "tetrahedron.hpp"

// globalnie lub wewnątrz maina
Cube cube;
CustomObject letter;
Kula kula;
Tetrahedron tetr;

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

    engine.setRenderCallback([&]() {
        // ustaw transformacje (przykład)
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, -5.0f);
        glRotatef((float)glutGet(GLUT_ELAPSED_TIME) * 0.02f, 0.1f, 1.0f, 0.5f);
        cube.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(3.0f, 0.0f, -5.0f);
        glRotatef((float)glutGet(GLUT_ELAPSED_TIME) * 0.02f, 1.0f, 0.0f, 0.0f);
        kula.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-3.0f, 0.0f, -5.0f);
        glRotatef((float)glutGet(GLUT_ELAPSED_TIME) * 0.02f, 1.0f, 0.0f, 0.0f);
        tetr.draw();
        glPopMatrix();

        // inny obiekt
        //glPushMatrix();
        //glTranslatef(1.5f, -0.2f, -4.0f);
        //letter.draw();
        //glPopMatrix();
        });

    engine.setUpdateCallback([&](double dt) {
        // Tutaj logika aktualizacji - dt w sekundach
        // Przykładowo nic nie robimy
        (void)dt;
        });

    engine.init(argc, argv);
    engine.start();

    return 0;
}
