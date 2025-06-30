 #include "scenes/scene_menu.h"
#include "core/scene_manager.h"
#include "ui/menu.h"
#include <raylib.h>
#include <stdio.h>

static Font menuFont;
static bool fontLoaded = false;

// Callbacks para los botones
static void onStart(void) {
    // Aquí cambiarías a la escena de juego (cuando esté implementada)
}
static void onSettings(void) {
    SceneManager_Change(SCENE_SETTINGS);
}
static void onExit(void) {
    CloseWindow();
}

static MenuButton menuButtons[] = {
    { "Comenzar", onStart },
    { "Ajustes", onSettings },
    { "Salir", onExit }
};
static MenuDef mainMenu;

#define MENU_BG_COLOR CLITERAL(Color){ 200, 200, 200, 255 }
#define LOGO_SPACE 110
#define OPTION_SPACE 64

void SceneMenu_Init(void) {
    if (!fontLoaded) {
        menuFont = LoadFont("assets/fonts/LuckiestGuy-Regular.ttf");
        fontLoaded = true;
    }
    // El menú inicia donde termina el logo (72 es el tamaño del logo)
    Menu_Init(&mainMenu, menuButtons, 3, menuFont, 40, OPTION_SPACE, LOGO_SPACE+72+60);
}

void SceneMenu_Update(void) {
    Menu_Update(&mainMenu, 960);
}

void SceneMenu_Draw(void) {
    int screenWidth = 960;
    int screenHeight = 540;
    ClearBackground(MENU_BG_COLOR);

    // Logo separado (puedes cambiarlo por un asset después)
    const char *logoText = "MY MANSION";
    float logoFontSize = 72;
    Vector2 logoSize = MeasureTextEx(menuFont, logoText, logoFontSize, 4);
    DrawTextEx(menuFont, logoText, (Vector2){ (screenWidth - logoSize.x)/2, LOGO_SPACE }, logoFontSize, 4, DARKGRAY);

    Menu_Draw(&mainMenu, screenWidth);
}
