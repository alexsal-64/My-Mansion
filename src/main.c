#include <raylib.h>
#include "core/scene_manager.h"
#include "core/game.h"
#include <math.h>

/*
    Dimensiones base internas del juego (relación de aspecto original).
    Cambia estos valores si quieres modificar la relación de aspecto base (por ejemplo, para 16:10).
*/
#define GAME_WIDTH 960
#define GAME_HEIGHT 540

/*
    Función principal:
    - Inicializa la ventana y el RenderTexture interno.
    - Controla el bucle principal del juego, incluyendo escalado y centrado profesional para ventana y pantalla completa.
    - Se asegura que el modo pantalla completa no dependa de la configuración o estiramiento previo de la ventana.
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

    // Variable para detectar cambios de modo (ventana <-> pantalla completa)
    bool wasFullscreen = IsWindowFullscreen();

    while (!WindowShouldClose()) {
        // Toggle pantalla completa con F
        if (IsKeyPressed(KEY_F)) {
            ToggleFullscreen();
        }

        // Detecta si el modo ha cambiado (ventana <-> pantalla completa)
        bool nowFullscreen = IsWindowFullscreen();
        if (nowFullscreen != wasFullscreen) {
            // Aquí podrías agregar lógica extra si necesitas actualizar recursos al cambiar de modo
            wasFullscreen = nowFullscreen;
        }

        SceneManager_Update();

        // --- Dibujar todo al RenderTexture interno ---
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);
            SceneManager_Draw(); // Dibuja la escena activa
        EndTextureMode();

        /*
            --- Escalado y centrado profesional ---
            Diferenciar entre modo ventana y pantalla completa:
            - En ventana, usar tamaño actual de la ventana.
            - En pantalla completa, usar resolución real del monitor actual.
            - El cálculo se hace SIEMPRE en cada frame, garantizando que la imagen en pantalla completa no dependa del tamaño previo de la ventana.
        */
        int windowWidth, windowHeight;
        if (IsWindowFullscreen()) {
            // Modo pantalla completa: obtener tamaño real del monitor
            int monitor = GetCurrentMonitor();
            windowWidth = GetMonitorWidth(monitor);
            windowHeight = GetMonitorHeight(monitor);
        } else {
            // Modo ventana: usar tamaño actual de la ventana
            windowWidth = GetScreenWidth();
            windowHeight = GetScreenHeight();
        }

        int scaledWidth, scaledHeight, offsetX, offsetY;

        if (g_pixelPerfectScaling) {
            // Escalado "Pixel Perfect": solo múltiplos enteros
            int scaleX = windowWidth / GAME_WIDTH;
            int scaleY = windowHeight / GAME_HEIGHT;
            int scale = (scaleX < scaleY) ? scaleX : scaleY;
            if (scale < 1) scale = 1;
            scaledWidth = GAME_WIDTH * scale;
            scaledHeight = GAME_HEIGHT * scale;
        } else {
            // Escalado "Suave": cualquier proporción, usa el menor para rellenar
            float scale = fminf(
                (float)windowWidth / GAME_WIDTH,
                (float)windowHeight / GAME_HEIGHT
            );
            scaledWidth = (int)roundf(GAME_WIDTH * scale);
            scaledHeight = (int)roundf(GAME_HEIGHT * scale);
        }

        // Centrado profesional (usa roundf para evitar errores de truncamiento)
        offsetX = (int)roundf((windowWidth - scaledWidth) / 2.0f);
        offsetY = (int)roundf((windowHeight - scaledHeight) / 2.0f);

        BeginDrawing();
            ClearBackground(BLACK); // Barras negras simétricas
            DrawTexturePro(
                target.texture,
                (Rectangle){ 0, 0, GAME_WIDTH, -GAME_HEIGHT }, // Vertical flip
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
