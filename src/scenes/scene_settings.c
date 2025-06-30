#include "scenes/scene_settings.h"
#include "core/scene_manager.h"
#include "ui/menu.h"
#include <raylib.h>
#include <stdio.h>

// Fuentes para cada tamaño a usar
static Font settingsFontMenu;    // 38px para botones
static Font settingsFontTitle;   // 56px para título
static Font settingsFontHint;    // 22px para hint
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
        settingsFontMenu  = LoadFontEx("assets/fonts/LuckiestGuy-Regular.ttf", 38, 0, 0);
        settingsFontTitle = LoadFontEx("assets/fonts/LuckiestGuy-Regular.ttf", 56, 0, 0);
        settingsFontHint  = LoadFontEx("assets/fonts/LuckiestGuy-Regular.ttf", 22, 0, 0);
        fontLoaded = true;
    }
    // El menú inicia debajo del título "Ajustes"
    Menu_Init(&settingsMenu, settingsButtons, 2, settingsFontMenu, 38, OPTION_SPACE, LOGO_SPACE+56+60);
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

    // Título centrado, usando fuente a 56px
    const char *title = "Ajustes";
    float titleSize = 56;
    float titleSpacing = 5;
    Vector2 titleDim = MeasureTextEx(settingsFontTitle, title, titleSize, titleSpacing);
    DrawTextEx(settingsFontTitle, title, (Vector2){(screenWidth-titleDim.x)/2, LOGO_SPACE}, titleSize, titleSpacing, DARKGRAY);

    Menu_Draw(&settingsMenu, screenWidth);

    // Hint centrado, usando fuente a 22px
    const char *hint = "Navega con Arriba/Abajo, selecciona con Enter/Espacio o Mouse";
    float hintFontSize = 22;
    float hintSpacing = 2;
    Vector2 hintDim = MeasureTextEx(settingsFontHint, hint, hintFontSize, hintSpacing);
    DrawTextEx(settingsFontHint, hint, (Vector2){(screenWidth-hintDim.x)/2, 480}, hintFontSize, hintSpacing, GRAY);
}

// (Opcional, pero profesional) Si tienes función de "unload" de la escena:
void SceneSettings_Unload(void) {
    if (fontLoaded) {
        UnloadFont(settingsFontMenu);
        UnloadFont(settingsFontTitle);
        UnloadFont(settingsFontHint);
        fontLoaded = false;
    }
}
