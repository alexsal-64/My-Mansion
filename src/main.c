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
    Solución avanzada e inteligente:
    - Se detecta el cambio entre ventana y pantalla completa y se fuerza una reinicialización de render si es necesario.
    - En modo ventana, el escalado y centrado se calculan según el tamaño actual de la ventana.
    - En modo pantalla completa, el escalado pixel perfect se calcula respecto a la resolución física del monitor.
    - Si la resolución del monitor no es múltiplo exacto, se ofrece un modo “stretch pixel perfect” (opcional, aquí implementado como ejemplo)
      para escalar y recortar los bordes, eliminando las barras negras.
    - El usuario puede alternar entre modo suave, pixel perfect clásico y pixel perfect stretch desde el menú de ajustes.
    - Este enfoque asegura que los modos sean completamente independientes y el juego siempre se adapte profesionalmente.
*/

typedef enum {
    PP_CENTERED, // Pixel perfect centrado (barras negras si es necesario)
    PP_STRETCH,  // Pixel perfect stretch/crop (recorta los bordes, sin barras negras)
} PixelPerfectMode;

int g_pixelPerfectScaling = 1;         // 1 = Pixel Perfect, 0 = Suave (control principal)
PixelPerfectMode g_pixelPerfectMode = PP_CENTERED; // Control avanzado del modo pixel perfect

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

        // Detectar cambio de modo y forzar reinicialización de RenderTexture si es necesario
        bool nowFullscreen = IsWindowFullscreen();
        if (nowFullscreen != wasFullscreen) {
            // En esta solución, el RenderTexture (target) se mantiene igual, ya que la fuente del juego es fija (GAME_WIDTH x GAME_HEIGHT).
            // Si quisieras un buffer de salida igual al monitor en modo stretch/crop real, podrías recargarlo aquí.
            wasFullscreen = nowFullscreen;
        }

        SceneManager_Update();

        // --- Dibujar todo al RenderTexture interno ---
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);
            SceneManager_Draw(); // Dibuja la escena activa
        EndTextureMode();

        /*
            --- Escalado y centrado avanzado ---
            Comportamiento completamente separado:
                - Ventana: cálculo según tamaño de la ventana.
                - Pantalla completa: cálculo según resolución física del monitor.
                - Pixel perfect stretch: escala y recorta para evitar barras, sólo en fullscreen.
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
        Rectangle srcRec = { 0, 0, GAME_WIDTH, -GAME_HEIGHT }; // Por defecto, toda la textura

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
            // Modo pixel perfect
            if (IsWindowFullscreen() && g_pixelPerfectMode == PP_STRETCH) {
                // Pixel perfect stretch/crop SOLO en pantalla completa
                // Escala entero "hacia arriba" para cubrir todo el monitor, recortando los bordes si es necesario
                int scaleX = (windowWidth + GAME_WIDTH - 1) / GAME_WIDTH;
                int scaleY = (windowHeight + GAME_HEIGHT - 1) / GAME_HEIGHT;
                int scale = (scaleX < scaleY) ? scaleX : scaleY;
                if (scale < 1) scale = 1;

                scaledWidth = GAME_WIDTH * scale;
                scaledHeight = GAME_HEIGHT * scale;
                offsetX = (windowWidth - scaledWidth) / 2;
                offsetY = (windowHeight - scaledHeight) / 2;

                // Recortar los bordes del source rectangle si se sale de pantalla
                // Ejemplo: si scaledWidth > windowWidth, recortamos srcRec.x y srcRec.width
                float cropX = 0, cropY = 0;
                float cropW = GAME_WIDTH, cropH = GAME_HEIGHT;
                if (scaledWidth > windowWidth) {
                    float over = (float)(scaledWidth - windowWidth) / scale;
                    cropX = over / 2.0f;
                    cropW -= over;
                }
                if (scaledHeight > windowHeight) {
                    float over = (float)(scaledHeight - windowHeight) / scale;
                    cropY = over / 2.0f;
                    cropH -= over;
                }
                srcRec.x = cropX;
                srcRec.y = cropY;
                srcRec.width = cropW;
                srcRec.height = -cropH; // Raylib invierte Y en RenderTexture
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
        }

        BeginDrawing();
            ClearBackground(BLACK); // Barras negras simétricas
            DrawTexturePro(
                target.texture,
                srcRec, // Puede estar recortado en stretch/crop
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
    - El modo pixel perfect stretch elimina las barras negras en fullscreen, recortando los bordes para un llenado total y máxima nitidez.
    - El modo pixel perfect clásico deja barras si la resolución del monitor no es múltiplo exacto.
    - El modo suave llena todo el área, sacrificando nitidez.
    - El usuario puede alternar entre estos modos en los ajustes, haciendo que el juego sea versátil y profesional en cualquier plataforma.
    - El cálculo de escalado y centrado es completamente independiente para ventana y pantalla completa.
    - Este enfoque es robusto, multiplataforma y listo para producción.
*/
