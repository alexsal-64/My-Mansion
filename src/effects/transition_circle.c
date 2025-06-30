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

    // 1. Prepara una textura de máscara
    RenderTexture2D mask = LoadRenderTexture(w, h);

    BeginTextureMode(mask);
        // Fondo negro, completamente opaco
        ClearBackground((Color){0, 0, 0, 255});
        // Círculo central transparente (alpha=0)
        DrawCircle(cx, cy, currentRadius, (Color){0, 0, 0, 0});
    EndTextureMode();

    // 2. Dibuja la máscara usando blending alpha
    BeginBlendMode(BLEND_ALPHA);
        DrawTextureRec(
            mask.texture,
            (Rectangle){0, 0, (float)w, -(float)h}, // flip Y
            (Vector2){0, 0},
            WHITE
        );
    EndBlendMode();

    UnloadRenderTexture(mask);
}

bool TransitionCircle_IsDone(void) {
    return finished;
}
