#include "Engine.hpp"

void Engine::init(int argc, char** argv) {
    // Inicjuj glut
    glutInit(&argc, argv);

    // Display mode
    int displayMode = 0;
    displayMode |= GLUT_RGB;
    if (cfg.doubleBuffer) displayMode |= GLUT_DOUBLE;
    if (cfg.depthBuffer) displayMode |= GLUT_DEPTH;
    // multisampling
    if (cfg.samples > 0) {
        glutSetOption(GLUT_MULTISAMPLE, cfg.samples);
        displayMode |= GLUT_MULTISAMPLE;
    }

    glutInitDisplayMode(displayMode);
    glutInitWindowSize(cfg.width, cfg.height);
    glutInitWindowPosition(100, 100);

    windowId = glutCreateWindow("Engine - freeglut + OpenGL");

    if (cfg.fullscreen) {
        glutFullScreen();
    }

    // Rejestracja callbacków (statyczne wrappery)
    glutDisplayFunc(&Engine::cbDisplay);
    glutReshapeFunc(&Engine::cbReshape);
    glutKeyboardFunc(&Engine::cbKeyboardDown);
    glutKeyboardUpFunc(&Engine::cbKeyboardUp);
    glutSpecialFunc(&Engine::cbSpecialDown);
    glutSpecialUpFunc(&Engine::cbSpecialUp);
    glutMouseFunc(&Engine::cbMouseButton);
    glutMotionFunc(&Engine::cbMouseMotion);
    glutPassiveMotionFunc(&Engine::cbMousePassiveMotion);
    glutCloseFunc(&Engine::cbClose);

    // Timer-based update loop using glutTimerFunc
    lastFrameTime = std::chrono::steady_clock::now();
    int ms = (cfg.targetFPS > 0) ? (1000 / cfg.targetFPS) : 16;
    glutTimerFunc(ms, &Engine::cbTimer, ms);

    // Dodatkowa inicjalizacja OpenGL
    initGL();
}

void Engine::start() {
	if (running) return;
	running = true;
	std::cout << "Starting main loop..." << std::endl;
	glutMainLoop(); // ta funkcja nie wychodzi aż do zamknięcia okna (w freeglut można użyć glutLeaveMainLoop)
}

void Engine::stop() {
    if (!running) return;
    running = false;
    // Poproś glut o zakończenie pętli
    glutLeaveMainLoop();
}

void Engine::clearScreen(float r, float g, float b, float a = 1.0f) {
    std::lock_guard<std::mutex> lock(stateMutex);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | (cfg.depthBuffer ? GL_DEPTH_BUFFER_BIT : 0));
}

void Engine::setProjection(ProjectionMode mode) {
    std::lock_guard<std::mutex> lock(stateMutex);
    cfg.projection = mode;
    applyProjection(cfg.width, cfg.height);
}

void Engine::toggleFullscreen() {
    std::lock_guard<std::mutex> lock(stateMutex);
    cfg.fullscreen = !cfg.fullscreen;
    if (cfg.fullscreen) glutFullScreen();
    else glutReshapeWindow(cfg.width, cfg.height);
}

void Engine::cleanup() {
    if (windowId != 0) {
        glutDestroyWindow(windowId);
        windowId = 0;
    }
    // dodatkowe czyszczenie zasobów graficznych jeśli były
}

void Engine::initGL() {
    // Podstawowe ustawienia OpenGL
    if (cfg.depthBuffer) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }
    if (cfg.samples > 0) {
        //glEnable(GL_MULTISAMPLE);
    }
    // Viewport i proj
    applyProjection(cfg.width, cfg.height);
}

void Engine::applyProjection(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / (float)h;
    if (cfg.projection == ProjectionMode::PERSPECTIVE) {
        // prosta funkcja gluPerspective (można zastąpić własną)
        float fH = tanf((cfg.fov / 2.0f) * 3.14159265f / 180.0f) * cfg.znear;
        // ręczne obliczenie matr. proj jest dłuższe; użyjemy gluPerspective jeżeli dostępne
#ifdef GLU_VERSION_1_3
        gluPerspective(cfg.fov, aspect, cfg.znear, cfg.zfar);
#else
// fallback na prostą frustum
        float top = cfg.znear * tanf(cfg.fov * 3.14159265f / 360.0f);
        float bottom = -top;
        float left = bottom * aspect;
        float right = top * aspect;
        glFrustum(left, right, bottom, top, cfg.znear, cfg.zfar);
#endif
    }
    else {
        // Orto: dopasuj do szerokości/ wysokości
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glOrtho(0, w, h, 0, -1, 1);
        glMatrixMode(GL_PROJECTION);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

Engine* Engine::s_instance = nullptr;