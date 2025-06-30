#include "transition_circle.h"
#include <raylib.h>
#include <math.h>

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
    int w = GetScreenWidth();
    int h = GetScreenHeight();
    int cx = w / 2;
    int cy = h / 2;
    float maxRadius = sqrtf((float)(w*w + h*h)) / 2.0f;
    float currentRadius = maxRadius * transitionProgress;

    // Dibuja un círculo negro opaco que va reduciendo su radio
    // Así, el círculo negro va "destapando" el menú
    DrawRectangle(0, 0, w, h, BLACK);
    DrawCircle(cx, cy, currentRadius, Fade(BLACK, 0.0f)); // círculo transparente (no cubre)
    DrawCircleLines(cx, cy, currentRadius, Fade(DARKGRAY, 0.3f)); // opcional: borde suave

    // Para el efecto: "recorta" el círculo simplemente no tapando esa zona
    // Si quieres un borde, puedes dibujar un círculo semitransparente alrededor
}

bool TransitionCircle_IsDone(void) {
    return finished;
}
