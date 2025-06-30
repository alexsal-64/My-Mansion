#include "scene_settings.h"
#include "scene_manager.h"
#include <raylib.h>
#include <stdio.h>

static Font settingsFont;
static bool fontLoaded = false;

void SceneSettings_Init(void) {
    if (!fontLoaded) {
        settingsFont = LoadFont("assets/fonts/LuckiestGuy-Regular.ttf");
        fontLoaded = true;
    }
}

void SceneSettings_Update(void) {
    // Volver al menú
    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_M)) {
        SceneManager_Change(SCENE_MENU);
    }
}

void SceneSettings_Draw(void) {
    ClearBackground(LIGHTGRAY);

    const char *title = "Ajustes";
    float titleSize = 60;
    Vector2 titleDim = MeasureTextEx(settingsFont, title, titleSize, 5);
    DrawTextEx(settingsFont, title, (Vector2){(960-titleDim.x)/2, 60}, titleSize, 5, DARKGRAY);

    const char *fullscreenHint = "F: Pantalla completa ON/OFF";
    DrawTextEx(settingsFont, fullscreenHint, (Vector2){200, 220}, 40, 2, RED);

    const char *backHint = "BACKSPACE o M: Volver al menu";
    DrawTextEx(settingsFont, backHint, (Vector2){200, 300}, 32, 2, DARKGRAY);

    const char *future = "Proximamente: Cambiar controles";
    DrawTextEx(settingsFont, future, (Vector2){260, 480}, 22, 2, GRAY);
}
