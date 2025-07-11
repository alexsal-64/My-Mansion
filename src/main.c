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
    SOLUCIÓN PROFESIONAL:
    - El modo ventana y el modo pantalla completa se tratan de forma completamente independiente.
    - En modo ventana:
        - El escalado "pixel perfect" usa la mayor escala entera que cabe en el tamaño actual de la ventana.
        - El escalado "suave" usa la mayor escala fraccional que respeta el aspect ratio.
    - En modo pantalla completa:
        - El escalado "pixel perfect" usa la mayor escala entera que cabe en la resolución física del monitor.
        - El escalado "suave" usa la mayor escala fraccional que respeta el aspect ratio y llena la pantalla.
    - Esto asegura que al cambiar entre ventana y pantalla completa, el cálculo se hace SIEMPRE respecto al contexto actual,
      sin heredar nada del modo anterior.
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

    while (!WindowShouldClose()) {
        // Toggle pantalla completa con F o desde el botón de ajustes (ambos llaman a ToggleFullscreen)
        if (IsKeyPressed(KEY_F)) {
            ToggleFullscreen();
        }

        SceneManager_Update();

        // --- Dibujar todo al RenderTexture interno ---
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);
            SceneManager_Draw(); // Dibuja la escena activa
        EndTextureMode();

        /*
            --- ESCALADO Y CENTRADO PROFESIONAL ---
            - El cálculo de escalado y centrado se basa SOLAMENTE en el modo actual:
              ventana: usa tamaño de la ventana
              pantalla completa: usa resolución física del monitor

            - Esto separa completamente los comportamientos, asegurando que al cambiar de modo,
              el juego SIEMPRE se escala y centra respecto al entorno actual, sin importar cómo estaba antes.
        */
        int windowWidth, windowHeight;

        if (IsWindowFullscreen()) {
            // Pantalla completa: obtener resolución física del monitor actual
            int monitor = GetCurrentMonitor();
            windowWidth = GetMonitorWidth(monitor);
            windowHeight = GetMonitorHeight(monitor);
        } else {
            // Ventana: usar tamaño actual de la ventana
            windowWidth = GetScreenWidth();
            windowHeight = GetScreenHeight();
        }

        int scaledWidth, scaledHeight, offsetX, offsetY;

        if (g_pixelPerfectScaling) {
            // ESCALADO PIXEL PERFECT
            // - Siempre usa la mayor escala entera posible
            int scaleX = windowWidth / GAME_WIDTH;
            int scaleY = windowHeight / GAME_HEIGHT;
            int scale = (scaleX < scaleY) ? scaleX : scaleY;
            if (scale < 1) scale = 1; // Nunca menos de 1x

            scaledWidth = GAME_WIDTH * scale;
            scaledHeight = GAME_HEIGHT * scale;
        } else {
            // ESCALADO SUAVE
            // - Usa la mayor escala fraccional posible que cabe en el área
            float scale = fminf(
                (float)windowWidth / GAME_WIDTH,
                (float)windowHeight / GAME_HEIGHT
            );
            scaledWidth = (int)roundf(GAME_WIDTH * scale);
            scaledHeight = (int)roundf(GAME_HEIGHT * scale);
        }

        // CENTRADO ABSOLUTO
        // - Calcula el offset para centrar el área escalada
        offsetX = (windowWidth - scaledWidth) / 2;
        offsetY = (windowHeight - scaledHeight) / 2;

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

/*
    EXPLICACIÓN DE MAESTRO:
    - El cálculo de escalado y centrado se basa SIEMPRE en el estado actual, nunca en el previo.
    - En modo ventana puedes estirar o maximizar: el juego se reescala según el tamaño de la ventana.
    - En modo pantalla completa, el juego SIEMPRE usa la resolución física del monitor para calcular el escalado,
      por lo que no hereda ninguna "configuración" de la ventana ni ninguna barra negra extra.
    - El modo pixel perfect puede dejar barras negras si la resolución del monitor no es múltiplo exacto de la base del juego,
      esto es normal y profesional en juegos 2D.
    - El modo suave rellena todo el área, aunque puede verse borroso.
    - Puedes cambiar entre modos en cualquier momento, y el juego recalcula y centra la imagen correctamente.

    Si necesitas forzar el modo suave sólo en pantalla completa, dime y te preparo ese ejemplo.
*/
