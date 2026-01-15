#pragma once
#include <GL/freeglut.h>

// Tryby cieniowania
enum ShadeMode {
    FLAT = 0,
    GOURAUD,
    PHONG_FIXED
};

// Funkcje do sterowania oświetleniem
namespace Lighting {
    extern bool enabled;
    extern ShadeMode shadeMode;

    void init();           // Ustawienia początkowe oświetlenia
    void apply();          // Włącz oświetlenie + cieniowanie
    void toggleLight();    // Włącz/wyłącz światło
    void setShadeMode(ShadeMode mode); // Zmiana cieniowania
}