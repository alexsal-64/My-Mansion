#include "ui/menu.h"
#include <raylib.h>

void Menu_Init(MenuDef *menu, MenuButton *buttons, int buttonCount, Font font, float fontSize, float spacing, int startY) {
    menu->buttons = buttons;
    menu->buttonCount = buttonCount;
    menu->selected = 0;
    menu->font = font;
    menu->fontSize = fontSize;
    menu->spacing = spacing;
    menu->startY = startY;
    menu->hovered = -1;
}

void Menu_Update(MenuDef *menu, int screenWidth) {
    // Teclado
    if (IsKeyPressed(KEY_UP)) {
        menu->selected = (menu->selected + menu->buttonCount - 1) % menu->buttonCount;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        menu->selected = (menu->selected + 1) % menu->buttonCount;
    }

    // Mouse (hover y click)
    menu->hovered = -1;
    Vector2 mouse = GetMousePosition();
    float baseY = menu->startY;
    for (int i = 0; i < menu->buttonCount; i++) {
        Vector2 optSize = MeasureTextEx(menu->font, menu->buttons[i].label, menu->fontSize, 2);
        float optX = (screenWidth - optSize.x) / 2;
        float optY = baseY + i * menu->spacing;

        Rectangle btnRect = { optX-12, optY-6, optSize.x+24, optSize.y+12 };
        if (CheckCollisionPointRec(mouse, btnRect)) {
            menu->hovered = i;
            menu->selected = i;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (menu->buttons[i].onSelect) menu->buttons[i].onSelect();
            }
        }
    }

    // Selección por teclado
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER) || IsKeyPressed(KEY_SPACE)) {
        if (menu->buttons[menu->selected].onSelect) {
            menu->buttons[menu->selected].onSelect();
        }
    }
}

void Menu_Draw(const MenuDef *menu, int screenWidth) {
    float baseY = menu->startY;
    for (int i = 0; i < menu->buttonCount; i++) {
        Vector2 optSize = MeasureTextEx(menu->font, menu->buttons[i].label, menu->fontSize, 2);
        float optX = (screenWidth - optSize.x) / 2;
        float optY = baseY + i * menu->spacing;

        Color color = (i == menu->selected) ? RED : BLACK;
        DrawTextEx(menu->font, menu->buttons[i].label, (Vector2){optX, optY}, menu->fontSize, 2, color);

        if (i == menu->selected) {
            DrawRectangleLines(optX-12, optY-6, optSize.x+24, optSize.y+12, color);
        }
    }
}
