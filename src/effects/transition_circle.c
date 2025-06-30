#include "effects/transition_circle.h"
#include <raylib.h>
#include <math.h>

#define GAME_WIDTH 960
#define GAME_HEIGHT 540
#define TRANSITION_DURATION 2.4f

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
    int w = GAME_WIDTH;
    int h = GAME_HEIGHT;
    int cx = w / 2;
    int cy = h / 2;

    float maxRadius = sqrtf((float)(w*w + h*h)) / 2.0f;
    float currentRadius = maxRadius * (1.0f - transitionProgress);

    if (currentRadius > 0.0f) {
        DrawCircle(cx, cy, currentRadius, BLACK);
    }
}
bool TransitionCircle_IsDone(void) {
    return finished;
}
