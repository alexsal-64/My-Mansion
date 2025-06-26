#include "transition_circle.h"
#include <raylib.h>
#include <math.h>

// Tiempo total de la transición (en segundos)
#define TRANSITION_DURATION 1.6f

static float transitionProgress = 0.0f;
static bool finished = false;

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
    // Fondo negro inicial
    ClearBackground(BLACK);

    // Centro de la pantalla lógica
    int cx = GetScreenWidth() / 2;
    int cy = GetScreenHeight() / 2;

    // Radio máximo para cubrir toda la pantalla (diagonal)
    float maxRadius = sqrtf((float)(GetScreenWidth()*GetScreenWidth() + GetScreenHeight()*GetScreenHeight())) / 2.0f;
    float currentRadius = maxRadius * transitionProgress;

    // Círculo "hueco" que crece y revela el fondo (efecto inverso)
    BeginBlendMode(BLEND_SUBTRACT_COLORS);
    DrawCircle(cx, cy, currentRadius, WHITE);
    EndBlendMode();
}

bool TransitionCircle_IsDone(void) {
    return finished;
}
