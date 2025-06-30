#include <raylib.h>
#include "scene_manager.h"
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
        // --- Procesa F para pantalla completa SIEMPRE ---
        if (IsKeyPressed(KEY_F)) {
            ToggleFullscreen();
        }

        SceneManager_Update();

        // --- Dibujar todo al RenderTexture interno ---
        BeginTextureMode(target);
            ClearBackground(RAYWHITE); // Fondo de la escena
            SceneManager_Draw();
        EndTextureMode();

        int windowWidth = GetScreenWidth();
        int windowHeight = GetScreenHeight();
        float scale = fminf(
            (float)windowWidth / GAME_WIDTH,
            (float)windowHeight / GAME_HEIGHT
        );
        int scaledWidth = (int)(GAME_WIDTH * scale);
        int scaledHeight = (int)(GAME_HEIGHT * scale);
        int offsetX = (windowWidth - scaledWidth) / 2;
        int offsetY = (windowHeight - scaledHeight) / 2;

        BeginDrawing();
            ClearBackground(BLACK); // Bordes negros (letterbox)
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
