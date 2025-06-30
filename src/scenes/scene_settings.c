#include "scenes/scene_settings.h"
#include "core/scene_manager.h"
#include "ui/menu.h"
#include <raylib.h>
#include <stdio.h>

static Font settingsFont;
static bool fontLoaded = false;

// Callbacks para los botones
static void onFullscreen(void) { ToggleFullscreen(); }
static void onBack(void) { SceneManager_Change(SCENE_MENU); }

static MenuButton settingsButtons[] = {
    { "Pantalla Completa ON/OFF", onFullscreen },
    { "Volver al menu", onBack }
};
static MenuDef settingsMenu;

#define MENU_BG_COLOR CLITERAL(Color){ 200, 200, 200, 255 }
#define LOGO_SPACE 90
#define OPTION_SPACE 68

void SceneSettings_Init(void) {
    if (!fontLoaded) {
        settingsFont = LoadFont("assets/fonts/LuckiestGuy-Regular.ttf");
        fontLoaded = true;
    }
    // El menú inicia debajo del título "Ajustes"
    Menu_Init(&settingsMenu, settingsButtons, 2, settingsFont, 38, OPTION_SPACE, LOGO_SPACE+56+60);
}

void SceneSettings_Update(void) {
    Menu_Update(&settingsMenu, 960);
    // Permitir volver al menú también con Backspace
    if (IsKeyPressed(KEY_BACKSPACE)) {
        SceneManager_Change(SCENE_MENU);
    }
}

void SceneSettings_Draw(void) {
    int screenWidth = 960;
    int screenHeight = 540;
    ClearBackground(MENU_BG_COLOR);

    // Título separado (puedes cambiarlo por un asset después)
    const char *title = "Ajustes";
    float titleSize = 56;
    Vector2 titleDim = MeasureTextEx(settingsFont, title, titleSize, 5);
    DrawTextEx(settingsFont, title, (Vector2){(screenWidth-titleDim.x)/2, LOGO_SPACE}, titleSize, 5, DARKGRAY);

    Menu_Draw(&settingsMenu, screenWidth);

 // Indicaciones para el usuario, centrado horizontalmente
    const char *hint = "Navega con Arriba/Abajo, selecciona con Enter/Espacio o Mouse";
    float hintFontSize = 22;
    float hintSpacing = 2;
    Vector2 hintDim = MeasureTextEx(settingsFont, hint, hintFontSize, hintSpacing);
    DrawTextEx(settingsFont, hint, (Vector2){(screenWidth-hintDim.x)/2, 480}, hintFontSize, hintSpacing, GRAY);
}
