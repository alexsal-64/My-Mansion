#include "transition_circle.h"
#include <raylib.h>
#include <math.h>

#define TRANSITION_DURATION 1.6f

static float transitionProgress = 0.0f;
static bool finished = false;

// Color del fondo del menú para "borrar" la máscara negra.
// Debe coincidir con el fondo de SceneMenu_Draw().
#define MENU_BG_COLOR CLITERAL(Color){ 200, 200, 200, 255 }

void TransitionCircle_Init(void) {
    transitionProgress = 0.0f;
    finished = false;
}

void TransitionCircle_Update(void) {
    if (!finished) {
        transitionProgress += GetFrameTime() / TRANSITION_DURATION;
        if (transitionProgress >= 1.0f) {
            transitionProgress = 1.0f;
            finished = true;
        }
    }
}

void TransitionCircle_Draw(void) {
    int w = GetScreenWidth();
    int h = GetScreenHeight();
    int cx = w / 2;
    int cy = h / 2;

    // Radio máximo, que cubre toda la pantalla
    float maxRadius = sqrtf((float)(w*w + h*h)) / 2.0f;
    // El círculo va creciendo desde 0 (centro) al máximo
    float currentRadius = maxRadius * transitionProgress;

    // 1. Tapa todo con un rectángulo negro
    DrawRectangle(0, 0, w, h, BLACK);

    // 2. Dibuja un círculo del color de fondo del menú, que "borra" la máscara negra
    DrawCircle(cx, cy, currentRadius, MENU_BG_COLOR);

    // Opcional: dibuja un borde suave alrededor para mejorar el efecto visual
    if (currentRadius > 5.0f) {
        DrawCircleLines(cx, cy, currentRadius, Fade(DARKGRAY, 0.3f));
    }
}

bool TransitionCircle_IsDone(void) {
    return finished;
}
