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
    int w = GetScreenWidth();
    int h = GetScreenHeight();
    int cx = w / 2;
    int cy = h / 2;
    float maxRadius = sqrtf((float)(w*w + h*h)) / 2.0f;
    float currentRadius = maxRadius * transitionProgress;

    // Crea una textura temporal (máscara)
    RenderTexture2D mask = LoadRenderTexture(w, h);

    // 1. Dibuja fondo negro en la máscara
    BeginTextureMode(mask);
        ClearBackground(BLACK);
        // Dibuja un círculo transparente (alpha = 0) para "abrir" el agujero
        DrawCircle(cx, cy, currentRadius, BLANK);
    EndTextureMode();

    // 2. Dibuja la máscara sobre la pantalla, usando blending multiplicativo para dejar ver debajo el agujero
    BeginBlendMode(BLEND_MULTIPLIED);
        DrawTextureRec(
            mask.texture,
            (Rectangle){0, 0, (float)w, -(float)h},
            (Vector2){0, 0},
            WHITE
        );
    EndBlendMode();

    UnloadRenderTexture(mask);
}

bool TransitionCircle_IsDone(void) {
    return finished;
}
