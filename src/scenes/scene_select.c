#include "scenes/scene_select.h"
#include "core/scene_manager.h"
#include "ui/menu.h"
#include <raylib.h>
#include <stdio.h>

// Fuentes separadas para cada tamaño
static Font selectFontTitle;    // 56px para el titulo
static Font selectFontButton;  // 38px para botones
static bool fontLoaded = false;

// Callbacks para los botones
static void scene1(void) {
    // Aquí cambiarías a la escena de juego (cuando esté implementada)
}
static void onBack(void) { SceneManager_Change(SCENE_MENU); }

// Label o etiquetas de letras
static MenuButton selectButtons[] = {
    { "Prueba escena 1", scene1 },
    { "Volver al menu", onBack }
};
static MenuDef selectMenu;

#define MENU_BG_COLOR CLITERAL(Color){ 200, 200, 200, 255 }
#define LOGO_SPACE 90
#define OPTION_SPACE 68

// Fuente usada
void SceneSelect_Init(void) {
    if (!fontLoaded) {
        selectFontTitle  = LoadFontEx("assets/fonts/LuckiestGuy-Regular.ttf", 56, 0, 0);
        selectFontButton = LoadFontEx("assets/fonts/LuckiestGuy-Regular.ttf", 38, 0, 0);
        fontLoaded = true;
    }
  // El menu inicia donde termina el titulo (56 el tamano)
    Menu_Init(&selectMenu, selectButtons, 2, selectFontButton, 38, OPTION_SPACE, LOGO_SPACE+56+60);
}

// llamado de actualizacion
void SceneSelect_Update(void) {
    Menu_Update(&selectMenu, 960);
    if (IsKeyPressed(KEY_BACKSPACE)) {
        SceneManager_Change(SCENE_MENU);
    }
}

// llamado de dibujado
void SceneSelect_Draw(void) {
    int screenWidth = 960;
    int screenHeight = 540;
    ClearBackground(MENU_BG_COLOR);

    // Titulo
    const char *title = "Test Seleccion de eventos";
    float titleSize = 56;
    float titleSpacing = 5;
    Vector2 titleDim = MeasureTextEx(selectFontTitle, title, titleSize, titleSpacing);
    DrawTextEx(selectFontTitle, title, (Vector2){(screenWidth-titleDim.x)/2, LOGO_SPACE}, titleSize, titleSpacing, DARKGRAY);

    Menu_Draw(&selectMenu, screenWidth);
}

// (Opcional, pero profesional) Liberar fuentes cuando ya no se usen
void SceneSelect_Unload(void) {
    if (fontLoaded) {
        UnloadFont(selectFontTitle);
        UnloadFont(selectFontButton);
        fontLoaded = false;
    }
}
