#include "scene_settings.h"
#include <raylib.h>
#include <stdio.h>

typedef struct {
    int width, height;
    const char *label;
} ResolutionOption;

// Resoluciones 16:9 compatibles, puedes agregar más si lo deseas
static ResolutionOption resolutions[] = {
    {1280, 720, "1280 x 720"},
    {1600, 900, "1600 x 900"},
    {1920, 1080, "1920 x 1080"},
    {2560, 1440, "2560 x 1440"},
    {3840, 2160, "3840 x 2160"}
};
static int resCount = sizeof(resolutions)/sizeof(resolutions[0]);
static int selectedRes = 0;

static Font settingsFont;
static bool fontLoaded = false;

void SceneSettings_Init(void) {
    // Encuentra la resolución actual para seleccionarla
    int w = GetScreenWidth();
    int h = GetScreenHeight();
    selectedRes = 0;
    for (int i = 0; i < resCount; i++) {
        if (resolutions[i].width == w && resolutions[i].height == h) {
            selectedRes = i;
            break;
        }
    }
    if (!fontLoaded) {
        settingsFont = LoadFont("assets/fonts/LuckiestGuy-Regular.ttf");
        fontLoaded = true;
    }
}

void SceneSettings_Update(void) {
    // Navegación
    if (IsKeyPressed(KEY_UP))   selectedRes = (selectedRes + resCount - 1) % resCount;
    if (IsKeyPressed(KEY_DOWN)) selectedRes = (selectedRes + 1) % resCount;

    // Cambiar resolución
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER) || IsKeyPressed(KEY_SPACE)) {
        SetWindowSize(resolutions[selectedRes].width, resolutions[selectedRes].height);
    }

    // Alternar pantalla completa
    if (IsKeyPressed(KEY_F11) || IsKeyPressed(KEY_F)) {
        ToggleFullscreen();
    }

    // Volver al menú
    if (IsKeyPressed(KEY_ESCAPE)) {
        // Cambia a la escena del menú (debes definir SceneManager_Change externamente)
        extern void SceneManager_Change(int newScene);
        SceneManager_Change(1); // 1 debe corresponder a SCENE_MENU en tu enum
    }
}

void SceneSettings_Draw(void) {
    ClearBackground(LIGHTGRAY);

    const char *title = "Ajustes";
    float titleSize = 60;
    Vector2 titleDim = MeasureTextEx(settingsFont, title, titleSize, 5);
    DrawTextEx(settingsFont, title, (Vector2){(1280-titleDim.x)/2, 60}, titleSize, 5, DARKGRAY);

    float baseY = 180;
    for (int i=0; i < resCount; i++) {
        float fontSize = 38;
        Vector2 resDim = MeasureTextEx(settingsFont, resolutions[i].label, fontSize, 2);
        float x = (1280 - resDim.x)/2;
        float y = baseY + i*54;
        Color color = (i == selectedRes) ? RED : BLACK;
        DrawTextEx(settingsFont, resolutions[i].label, (Vector2){x, y}, fontSize, 2, color);
        if (i == selectedRes)
            DrawRectangleLines(x-10, y-4, resDim.x+20, resDim.y+8, color);
    }

    const char *hint = "ENTER: Cambiar resolucion  |  F11: Pantalla completa  |  ESC: Volver";
    DrawTextEx(settingsFont, hint, (Vector2){80, 650}, 26, 2, DARKGRAY);

    // Próximamente: cambiar controles...
    DrawTextEx(settingsFont, "Proximamente: Cambiar controles", (Vector2){420, 600}, 22, 2, GRAY);
}
