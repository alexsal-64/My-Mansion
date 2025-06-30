#ifndef UI_MENU_H
#define UI_MENU_H

#include <raylib.h>

typedef struct MenuButton {
    const char *label;
    void (*onSelect)(void);
} MenuButton;

typedef struct MenuDef {
    MenuButton *buttons;
    int buttonCount;
    int selected;
    Font font;
    float fontSize;
    float spacing;
    int startY;
    int hovered; // índice del botón sobre el que está el mouse, -1 si ninguno
} MenuDef;

// Inicializa una estructura MenuDef
void Menu_Init(MenuDef *menu, MenuButton *buttons, int buttonCount, Font font, float fontSize, float spacing, int startY);

// Maneja input de teclado y mouse, ejecuta callbacks cuando corresponde
void Menu_Update(MenuDef *menu, int screenWidth);

// Dibuja el menú de botones
void Menu_Draw(const MenuDef *menu, int screenWidth);

#endif // UI_MENU_H
