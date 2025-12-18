// Engine_OpenGL_freeglut.cpp
// Kompletny przykład klasy Engine do użycia z OpenGL + freeglut
// Zawiera implementację inicjalizacji, parametryzowania trybu graficznego,
// obsługi wejścia (klawiatura, mysz), głównej pętli opartej na timerze,
// czyszczenia ekranu, zmiany rzutowania, oraz sprzątania zasobów.
// Kompilacja (Linux): g++ Engine_OpenGL_freeglut.cpp -lGL -lGLU -lglut -std=c++11 -o engine

#include <GL/freeglut.h>
#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include <mutex>

// Prosty enum rzutowań
enum class ProjectionMode { PERSPECTIVE, ORTHOGRAPHIC };

class Engine {
public:
    // Konfiguracja graficzna
    struct Config {
        int width = 800;
        int height = 600;
        bool fullscreen = false;
        bool borderless = false; // jeżeli implementowalibyśmy
        bool doubleBuffer = true;
        bool depthBuffer = true;
        bool vsync = true; // zależy od implementacji sterownika
        int samples = 0; // multisampling
        ProjectionMode projection = ProjectionMode::PERSPECTIVE;
        float fov = 60.0f;
        float znear = 0.1f;
        float zfar = 1000.0f;
        int targetFPS = 60; // docelowe FPS
        bool enableKeyboard = true;
        bool enableMouse = true;
    };

private:
    static Engine* s_instance; // singleton pomocniczy do callbacków
    Config cfg;
    int windowId = 0;
    bool running = false;
    std::chrono::steady_clock::time_point lastFrameTime;
    std::mutex stateMutex;

    // Stan wejścia
    bool keyDown[256] = { 0 };
    bool specialDown[256] = { 0 };
    int mouseX = 0, mouseY = 0;
    bool mouseButtons[3] = { 0 };

    // Użytkownicy mogą podłączyć własne funkcje
    std::function<void(double)> onUpdate; // delta time in seconds
    std::function<void()> onRender;

public:
    Engine(const Config& config = Config()) : cfg(config) {
        s_instance = this;
    }

    ~Engine() {
        cleanup();
    }

    // ---------------------- Inicjalizacja ----------------------
    void init(int argc, char** argv);

    void start();

    void stop();

    // ---------------------- Callback setters ----------------------
    void setUpdateCallback(std::function<void(double)> cb) { onUpdate = cb; }
    void setRenderCallback(std::function<void()> cb) { onRender = cb; }

    // ---------------------- Render / update / utilities ----------------------
    void clearScreen(float r, float g, float b, float a );

    void setProjection(ProjectionMode mode);

    void toggleFullscreen();

    // ---------------------- Cleanup ----------------------
    void cleanup();

private:
    void initGL();

    void applyProjection(int w, int h);

    // ---------------------- Static callback wrappers ----------------------
    static void cbDisplay() {
        if (!s_instance) return;
        s_instance->display();
    }

    static void cbReshape(int w, int h) {
        if (!s_instance) return;
        s_instance->reshape(w, h);
    }

    static void cbTimer(int value) {
        if (!s_instance) return;
        s_instance->timer(value);
    }

    static void cbKeyboardDown(unsigned char key, int x, int y) {
        if (!s_instance) return;
        s_instance->keyboardDown(key, x, y);
    }

    static void cbKeyboardUp(unsigned char key, int x, int y) {
        if (!s_instance) return;
        s_instance->keyboardUp(key, x, y);
    }

    static void cbSpecialDown(int key, int x, int y) {
        if (!s_instance) return;
        s_instance->specialKeyDown(key, x, y);
    }

    static void cbSpecialUp(int key, int x, int y) {
        if (!s_instance) return;
        s_instance->specialKeyUp(key, x, y);
    }

    static void cbMouseButton(int button, int state, int x, int y) {
        if (!s_instance) return;
        s_instance->mouseButton(button, state, x, y);
    }

    static void cbMouseMotion(int x, int y) {
        if (!s_instance) return;
        s_instance->mouseMotion(x, y);
    }

    static void cbMousePassiveMotion(int x, int y) {
        if (!s_instance) return;
        s_instance->mousePassiveMotion(x, y);
    }

    static void cbClose() {
        if (!s_instance) return;
        s_instance->close();
    }

    // ---------------------- Instance methods for callbacks ----------------------
    void display() {
        // This function is called when GLUT requests a redraw
        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT | (cfg.depthBuffer ? GL_DEPTH_BUFFER_BIT : 0));

        if (onRender) onRender();

        if (cfg.doubleBuffer) glutSwapBuffers();
        else glFlush();
    }

    void reshape(int w, int h) {
        std::lock_guard<std::mutex> lock(stateMutex);
        cfg.width = w;
        cfg.height = h;
        applyProjection(w, h);
    }

    void timer(int value) {
        // Oblicz delta time
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - lastFrameTime;
        double dt = elapsed.count();
        lastFrameTime = now;

        // Wywołaj update
        if (onUpdate) onUpdate(dt);

        // Zleć rysowanie
        glutPostRedisplay();

        // Zarejestruj następne wywołanie
        int ms = (cfg.targetFPS > 0) ? (1000 / cfg.targetFPS) : 16;
        glutTimerFunc(ms, &Engine::cbTimer, ms);
    }

    void keyboardDown(unsigned char key, int x, int y) {
        if (!cfg.enableKeyboard) return;
        keyDown[key & 0xFF] = true;
        // Kilka prostych akcji domyślnych
        if (key == 27) { // ESC
            stop();
        }
        else if (key == 'f' || key == 'F') {
            toggleFullscreen();
        }
        else if (key == 'p' || key == 'P') {
            // zmiana rzutowania jako przykład
            setProjection(cfg.projection == ProjectionMode::PERSPECTIVE ? ProjectionMode::ORTHOGRAPHIC : ProjectionMode::PERSPECTIVE);
        }
    }

    void keyboardUp(unsigned char key, int x, int y) {
        if (!cfg.enableKeyboard) return;
        keyDown[key & 0xFF] = false;
    }

    void specialKeyDown(int key, int x, int y) {
        if (!cfg.enableKeyboard) return;
        if (key < 256) specialDown[key] = true;
    }

    void specialKeyUp(int key, int x, int y) {
        if (!cfg.enableKeyboard) return;
        if (key < 256) specialDown[key] = false;
    }

    void mouseButton(int button, int state, int x, int y) {
        if (!cfg.enableMouse) return;
        if (button >= 0 && button < 3) {
            mouseButtons[button] = (state == GLUT_DOWN);
        }
        mouseX = x; mouseY = y;
    }

    void mouseMotion(int x, int y) {
        if (!cfg.enableMouse) return;
        mouseX = x; mouseY = y;
    }

    void mousePassiveMotion(int x, int y) {
        if (!cfg.enableMouse) return;
        mouseX = x; mouseY = y;
    }

    void close() {
        // Sprzątanie
        cleanup();
    }
};



