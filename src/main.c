#include <raylib.h>

int main(void) {
    // Inicializa la ventana de raylib
    InitWindow(800, 600, "Mansion - Prueba Inicial");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("¡Hola, Raylib en Linux!", 190, 280, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
