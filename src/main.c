#include <raylib.h>
#include "scene_manager.h"

#define GAME_WIDTH 1280
#define GAME_HEIGHT 720

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "My Mansion - Menu Inicial");

    // RenderTexture para dibujar el juego
    RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

    SetTargetFPS(60);
    SceneManager_Init();

    while (!WindowShouldClose()) {
        SceneManager_Update();

        // --- Dibujar todo al RenderTexture interno ---
        BeginTextureMode(target);
            ClearBackground(RAYWHITE); // Fondo de la escena
            SceneManager_Draw();
        EndTextureMode();

        // --- Escalar el RenderTexture a la ventana actual ---
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
                (Rectangle){ 0, 0, GAME_WIDTH, -GAME_HEIGHT }, // Y negativo por el flip Y de raylib
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
