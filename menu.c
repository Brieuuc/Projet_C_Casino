#include "raylib.h"
#include "menu.h"
int DrawMenu(int screenWidth, int screenHeight) {
    const char *menuText = "Menu Principal";
    const char *game1Button = "Chicken Game";
    const char *game2Button = "INDISPONIBLE";
    const char *game3Button = "INDISPONIBLE";
    const char *statsButton = "STATISTICS";

    int menuFontSize = 30;
    int buttonFontSize = 20;

    int menuTextWidth = MeasureText(menuText, menuFontSize);
    int buttonWidth = MeasureText(game1Button, buttonFontSize) + 20;
    int buttonHeight = buttonFontSize + 20;

    Rectangle button1 = {
        (screenWidth - buttonWidth) / 2,
        screenHeight * 0.4,
        buttonWidth,
        buttonHeight
    };

    Rectangle button2 = {
        (screenWidth - buttonWidth) / 2,
        screenHeight * 0.5,
        buttonWidth,
        buttonHeight
    };

    Rectangle button3 = {
        (screenWidth - buttonWidth) / 2,
        screenHeight * 0.6,
        buttonWidth,
        buttonHeight
    };

    Rectangle button4 = {
        (screenWidth - buttonWidth) / 2,
        screenHeight * 0.7,
        buttonWidth,
        buttonHeight
    };

    DrawText(menuText, (screenWidth - menuTextWidth) / 2, screenHeight * 0.3, menuFontSize, YELLOW);

    // Dessiner les boutons
    DrawRectangleRec(button1, LIGHTGRAY);
    DrawText(game1Button, button1.x + (button1.width - MeasureText(game1Button, buttonFontSize)) / 2,
             button1.y + (button1.height - buttonFontSize) / 2, buttonFontSize, BLACK);

    DrawRectangleRec(button2, DARKGRAY);
    DrawText(game2Button, button2.x + (button2.width - MeasureText(game2Button, buttonFontSize)) / 2,
             button2.y + (button2.height - buttonFontSize) / 2, buttonFontSize, BLACK);

    DrawRectangleRec(button3, DARKGRAY);
    DrawText(game3Button, button3.x + (button3.width - MeasureText(game3Button, buttonFontSize)) / 2,
             button3.y + (button3.height - buttonFontSize) / 2, buttonFontSize, BLACK);

    DrawRectangleRec(button4, LIGHTGRAY);
    DrawText(statsButton, button4.x + (button4.width - MeasureText(statsButton, buttonFontSize)) / 2,
             button4.y + (button4.height - buttonFontSize) / 2, buttonFontSize, BLACK);

    // Vérifier si un bouton est cliqué et retourner la valeur correspondante
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), button1)) {
            return 1;  // Jeu 1 sélectionné
        }
        if (CheckCollisionPointRec(GetMousePosition(), button2)) {
            return 2;  // Jeu 2 sélectionné
        }
        if (CheckCollisionPointRec(GetMousePosition(), button3)) {
            return 3;  // Jeu 3 sélectionné
        }
        if (CheckCollisionPointRec(GetMousePosition(), button4)) {
            return 4;  // Statistiques sélectionnées
        }
    }

    return 0;
}
