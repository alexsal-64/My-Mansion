#include <raylib.h>
#include "core/scene_manager.h"
#include "game.h"
#include <math.h>

#define GAME_WIDTH 960
#define GAME_HEIGHT 540

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "My Mansion - Menu Inicial");

    RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

    SetTargetFPS(60);
    SceneManager_Init();

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_F)) {
            ToggleFullscreen();
        }

        SceneManager_Update();

        // --- Dibujar todo al RenderTexture interno ---
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);
            SceneManager_Draw();
        EndTextureMode();

        int windowWidth = GetScreenWidth();
        int windowHeight = GetScreenHeight();

        int scaledWidth, scaledHeight, offsetX, offsetY;
        if (g_pixelPerfectScaling) {
            int scaleX = windowWidth / GAME_WIDTH;
            int scaleY = windowHeight / GAME_HEIGHT;
            int scale = (scaleX < scaleY) ? scaleX : scaleY;
            if (scale < 1) scale = 1;
            scaledWidth = GAME_WIDTH * scale;
            scaledHeight = GAME_HEIGHT * scale;
        } else {
            float scale = fminf(
                (float)windowWidth / GAME_WIDTH,
                (float)windowHeight / GAME_HEIGHT
            );
            scaledWidth = (int)(GAME_WIDTH * scale);
            scaledHeight = (int)(GAME_HEIGHT * scale);
        }
        offsetX = (windowWidth - scaledWidth) / 2;
        offsetY = (windowHeight - scaledHeight) / 2;

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(
                target.texture,
                (Rectangle){ 0, 0, GAME_WIDTH, -GAME_HEIGHT },
                (Rectangle){ offsetX, offsetY, scaledWidth, scaledHeight },
                (Vector2){ 0, 0 },
                0.0f,
                WHITE
            );
        EndDrawing();
    }

    UnloadRenderTexture(target);
    SceneManager_Unload();
    CloseWindow();
    return 0;
}
