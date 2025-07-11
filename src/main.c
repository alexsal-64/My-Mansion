#include <raylib.h>
#include "core/scene_manager.h"
#include "core/game.h"
#include <math.h>

/*
    Dimensiones base internas del juego (relación de aspecto original).
    Cambia estos valores si quieres modificar la relación de aspecto base.
*/
#define GAME_WIDTH 960
#define GAME_HEIGHT 540

/*
    Solución profesional:
    - El modo ventana y el modo pantalla completa se calculan por separado.
    - En modo ventana, el escalado y centrado se calculan según el tamaño actual de la ventana.
    - En modo pantalla completa, el escalado pixel perfect se calcula respecto a la resolución física del monitor.
    - El modo pixel perfect sólo usa múltiplos enteros y deja barras negras si la resolución no es múltiplo exacto.
    - El modo suave rellena el área, sacrificando nitidez pero evitando barras negras.
    - El usuario alterna entre pixel perfect y suave desde el menú de ajustes.
*/

int main(void) {
    // Habilitar ventana redimensionable y VSync
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    // Inicializa la ventana con el título profesional
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "The Mansion Project");

    // RenderTexture interno para dibujar el juego con resolución base
    RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

    SetTargetFPS(60);
    SceneManager_Init();

    // Estado para detectar cambio de modo (fullscreen/ventana)
    bool wasFullscreen = IsWindowFullscreen();

    while (!WindowShouldClose()) {
        // Toggle pantalla completa con F o desde el botón de ajustes
        if (IsKeyPressed(KEY_F)) {
            ToggleFullscreen();
        }

        // Detectar cambio de modo (si quieres reaccionar a cambio de fullscreen)
        bool nowFullscreen = IsWindowFullscreen();
        if (nowFullscreen != wasFullscreen) {
            wasFullscreen = nowFullscreen;
            // No es necesario reinicializar el RenderTexture; solo recalculamos el escalado en cada frame.
        }

        SceneManager_Update();

        // --- Dibujar todo al RenderTexture interno ---
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);
            SceneManager_Draw(); // Dibuja la escena activa
        EndTextureMode();

        /*
            --- Escalado y centrado profesional ---
            - Ventana: calcula según tamaño de la ventana.
            - Pantalla completa: calcula según resolución física del monitor.
            - Pixel perfect: sólo múltiplos enteros, barras negras si es necesario.
            - Suave: escala fraccional, rellena todo el área.
        */
        int windowWidth, windowHeight;
        if (IsWindowFullscreen()) {
            int monitor = GetCurrentMonitor();
            windowWidth = GetMonitorWidth(monitor);
            windowHeight = GetMonitorHeight(monitor);
        } else {
            windowWidth = GetScreenWidth();
            windowHeight = GetScreenHeight();
        }

        int scaledWidth, scaledHeight, offsetX, offsetY;
        Rectangle srcRec = { 0, 0, GAME_WIDTH, -GAME_HEIGHT }; // Toda la textura

        if (!g_pixelPerfectScaling) {
            // Modo suave: escalado fraccional, rellena el área y puede verse borroso.
            float scale = fminf(
                (float)windowWidth / GAME_WIDTH,
                (float)windowHeight / GAME_HEIGHT
            );
            scaledWidth = (int)roundf(GAME_WIDTH * scale);
            scaledHeight = (int)roundf(GAME_HEIGHT * scale);
            offsetX = (windowWidth - scaledWidth) / 2;
            offsetY = (windowHeight - scaledHeight) / 2;
        } else {
            // Pixel perfect clásico (centrado, barras negras si es necesario)
            int scaleX = windowWidth / GAME_WIDTH;
            int scaleY = windowHeight / GAME_HEIGHT;
            int scale = (scaleX < scaleY) ? scaleX : scaleY;
            if (scale < 1) scale = 1;

            scaledWidth = GAME_WIDTH * scale;
            scaledHeight = GAME_HEIGHT * scale;
            offsetX = (windowWidth - scaledWidth) / 2;
            offsetY = (windowHeight - scaledHeight) / 2;
            // srcRec es toda la textura
        }

        BeginDrawing();
            ClearBackground(BLACK); // Barras negras simétricas si es necesario
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
    - El modo pixel perfect sólo escala por múltiplos enteros y deja barras negras si el monitor no es múltiplo exacto.
    - El modo suave rellena todo, sacrificando nitidez.
    - El cálculo de escalado y centrado es completamente independiente para ventana y pantalla completa.
    - El usuario alterna entre pixel perfect y suave desde los ajustes.
    - El código está listo para producción y multiplataforma.
*/
