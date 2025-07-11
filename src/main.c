#include <raylib.h>
#include "core/scene_manager.h"
#include "core/game.h"
#include <math.h>

/*
    Dimensiones base internas del juego (relación de aspecto original).
*/
#define GAME_WIDTH 960
#define GAME_HEIGHT 540

/*
    Solución profesional:
    - La ventana NO se puede redimensionar ni maximizar.
    - El usuario solo puede mover la ventana (drag).
    - El botón de pantalla completa sigue funcionando y el escalado se calcula profesionalmente según el modo.
    - Evita cualquier problema de escalado variable en ventana.
*/

int main(void) {
    // Solo VSync, NO resizable
    SetConfigFlags(FLAG_VSYNC_HINT);

    // Inicializa la ventana con tamaño fijo y título profesional
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "The Mansion Project");

    // RenderTexture interno para dibujar el juego con resolución base
    RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

    SetTargetFPS(60);
    SceneManager_Init();

    bool wasFullscreen = IsWindowFullscreen();

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_F)) {
            ToggleFullscreen();
        }

        bool nowFullscreen = IsWindowFullscreen();
        if (nowFullscreen != wasFullscreen) {
            wasFullscreen = nowFullscreen;
        }

        SceneManager_Update();

        // --- Dibujar todo al RenderTexture interno ---
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);
            SceneManager_Draw();
        EndTextureMode();

        int windowWidth, windowHeight;
        if (IsWindowFullscreen()) {
            int monitor = GetCurrentMonitor();
            windowWidth = GetMonitorWidth(monitor);
            windowHeight = GetMonitorHeight(monitor);
        } else {
            // Ventana fija: siempre GAME_WIDTH x GAME_HEIGHT
            windowWidth = GAME_WIDTH;
            windowHeight = GAME_HEIGHT;
        }

        int scaledWidth, scaledHeight, offsetX, offsetY;
        Rectangle srcRec = { 0, 0, GAME_WIDTH, -GAME_HEIGHT };

        if (!g_pixelPerfectScaling) {
            float scale = fminf(
                (float)windowWidth / GAME_WIDTH,
                (float)windowHeight / GAME_HEIGHT
            );
            scaledWidth = (int)roundf(GAME_WIDTH * scale);
            scaledHeight = (int)roundf(GAME_HEIGHT * scale);
            offsetX = (windowWidth - scaledWidth) / 2;
            offsetY = (windowHeight - scaledHeight) / 2;
        } else {
            int scaleX = windowWidth / GAME_WIDTH;
            int scaleY = windowHeight / GAME_HEIGHT;
            int scale = (scaleX < scaleY) ? scaleX : scaleY;
            if (scale < 1) scale = 1;

            scaledWidth = GAME_WIDTH * scale;
            scaledHeight = GAME_HEIGHT * scale;
            offsetX = (windowWidth - scaledWidth) / 2;
            offsetY = (windowHeight - scaledHeight) / 2;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(
                target.texture,
                srcRec,
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

/*
    Maestro explica:
    - La ventana nunca cambia de tamaño ni se maximiza, sólo se puede mover.
    - El botón/tecla de pantalla completa funciona y el escalado se adapta profesionalmente.
    - Así NO tendrás problemas de escalado variable ni pixel perfect en ventana.
    - Código listo para producción y multiplataforma.
*/
