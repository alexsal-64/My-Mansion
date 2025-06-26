#include <raylib.h>
#include "scene_manager.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My Mansion - Menu Inicial");
    SetTargetFPS(60);

    SceneManager_Init();

    while (!WindowShouldClose()) {
        SceneManager_Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        SceneManager_Draw();
        EndDrawing();
    }

    SceneManager_Unload();
    CloseWindow();
    return 0;
}
