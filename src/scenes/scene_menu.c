#include "scene_menu.h"
#include "scene_manager.h" // <-- ¡Incluye el manager para cambiar de escena!
#include <raylib.h>
#include <stdio.h>

#define MENU_OPTION_COUNT 3

static const char *menuOptions[MENU_OPTION_COUNT] = {
    "Comenzar",
    "Ajustes",
    "Salir"
};

static int selectedOption = 0;
static Font menuFont;
static bool fontLoaded = false;

// Para centrar y espaciar el logo y opciones
#define MENU_BG_COLOR CLITERAL(Color){ 200, 200, 200, 255 }
#define LOGO_SPACE 110
#define OPTION_SPACE 64

void SceneMenu_Init(void) {
    selectedOption = 0;
    if (!fontLoaded) {
        menuFont = LoadFont("assets/fonts/LuckiestGuy-Regular.ttf");
        fontLoaded = true;
    }
}

void SceneMenu_Update(void) {
    // Navegación de menú (arriba/abajo)
    if (IsKeyPressed(KEY_UP)) {
        selectedOption = (selectedOption + MENU_OPTION_COUNT - 1) % MENU_OPTION_COUNT;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        selectedOption = (selectedOption + 1) % MENU_OPTION_COUNT;
    }

    // Selección de opción (Enter)
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER) || IsKeyPressed(KEY_SPACE)) {
        switch (selectedOption) {
            case 0: /* Comenzar */
                // Aquí cambiarías a la escena de juego (cuando esté implementada)
                break;
            case 1: /* Ajustes */
                SceneManager_Change(SCENE_SETTINGS); // <--- Cambio profesional a Ajustes
                break;
            case 2: /* Salir */
                CloseWindow();
                break;
        }
    }
}

void SceneMenu_Draw(void) {
    int screenWidth = 960; // Debe coincidir con el espacio lógico
    int screenHeight = 540;

    // Fondo gris
    ClearBackground(MENU_BG_COLOR);

    // Logo placeholder (puedes reemplazar por un DrawTexture en el futuro)
    const char *logoText = "MY MANSION";
    float logoFontSize = 72;
    Vector2 logoSize = MeasureTextEx(menuFont, logoText, logoFontSize, 4);
    DrawTextEx(menuFont, logoText,
        (Vector2){ (screenWidth - logoSize.x)/2, LOGO_SPACE },
        logoFontSize, 4, DARKGRAY);

    // Opciones de menú
    float baseY = LOGO_SPACE + logoSize.y + 60;
    for (int i = 0; i < MENU_OPTION_COUNT; i++) {
        float fontSize = 40;
        Vector2 optSize = MeasureTextEx(menuFont, menuOptions[i], fontSize, 2);
        float optX = (screenWidth - optSize.x) / 2;
        float optY = baseY + i*OPTION_SPACE;

        Color color = (i == selectedOption) ? RED : BLACK;
        DrawTextEx(menuFont, menuOptions[i], (Vector2){optX, optY}, fontSize, 2, color);

        // Sombra para la opción seleccionada
        if (i == selectedOption) {
            DrawRectangleLines(optX-12, optY-6, optSize.x+24, optSize.y+12, color);
        }
    }
}
