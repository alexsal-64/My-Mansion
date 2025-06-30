#include "scene_settings.h"
#include "scene_manager.h"
#include <raylib.h>
#include <stdio.h>

#define SETTINGS_OPTION_COUNT 2

static const char *settingsOptions[SETTINGS_OPTION_COUNT] = {
    "Pantalla Completa",
    "Volver al menu"
};

static int selectedOption = 0;
static Font settingsFont;
static bool fontLoaded = false;

#define MENU_BG_COLOR CLITERAL(Color){ 200, 200, 200, 255 }
#define LOGO_SPACE 90
#define OPTION_SPACE 68

void SceneSettings_Init(void) {
    selectedOption = 0;
    if (!fontLoaded) {
        settingsFont = LoadFont("assets/fonts/LuckiestGuy-Regular.ttf");
        fontLoaded = true;
    }
}

void SceneSettings_Update(void) {
    // Navegación con flechas
    if (IsKeyPressed(KEY_UP)) {
        selectedOption = (selectedOption + SETTINGS_OPTION_COUNT - 1) % SETTINGS_OPTION_COUNT;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        selectedOption = (selectedOption + 1) % SETTINGS_OPTION_COUNT;
    }

    // Selección por teclado
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER) || IsKeyPressed(KEY_SPACE)) {
        switch (selectedOption) {
            case 0: // Pantalla completa
                ToggleFullscreen();
                break;
            case 1: // Volver
                SceneManager_Change(SCENE_MENU);
                break;
        }
    }
}

void SceneSettings_Draw(void) {
    int screenWidth = 960;
    int screenHeight = 540;
    ClearBackground(MENU_BG_COLOR);

    // Título
    const char *title = "Ajustes";
    float titleSize = 56;
    Vector2 titleDim = MeasureTextEx(settingsFont, title, titleSize, 5);
    DrawTextEx(settingsFont, title, (Vector2){(screenWidth-titleDim.x)/2, LOGO_SPACE}, titleSize, 5, DARKGRAY);

    // Opciones
    float baseY = LOGO_SPACE + titleDim.y + 60;
    for (int i = 0; i < SETTINGS_OPTION_COUNT; i++) {
        float fontSize = 38;
        Vector2 optSize = MeasureTextEx(settingsFont, settingsOptions[i], fontSize, 2);
        float optX = (screenWidth - optSize.x) / 2;
        float optY = baseY + i*OPTION_SPACE;

        Color color = (i == selectedOption) ? RED : BLACK;
        DrawTextEx(settingsFont, settingsOptions[i], (Vector2){optX, optY}, fontSize, 2, color);

        if (i == selectedOption) {
            DrawRectangleLines(optX-12, optY-6, optSize.x+24, optSize.y+12, color);
        }
    }

    // Indicaciones
    const char *hint = "Navega con ↑/↓, selecciona con Enter o Espacio";
    DrawTextEx(settingsFont, hint, (Vector2){screenWidth/2-220, 480}, 22, 2, GRAY);
}
