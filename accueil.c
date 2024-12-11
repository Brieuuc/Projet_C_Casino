#include "raylib.h"
#include "accueil.h"

int DrawAccueil(int screenWidth, int screenHeight) {
    const char *welcomeText = "Bienvenue au casino";
    const char *titleText = "Brieuc's Casino";
    const char *buttonText = "ENTRER";
    int titleFontSize = 30;
    int welcomeFontSize = 20;
    int buttonFontSize = 20;

    int titleTextWidth = MeasureText(titleText, titleFontSize);
    int welcomeTextWidth = MeasureText(welcomeText, welcomeFontSize);
    int buttonWidth = welcomeTextWidth + 20;
    int buttonHeight = buttonFontSize + 20;

    Rectangle button = {
        (screenWidth - buttonWidth) / 2,
        screenHeight * 0.55,
        buttonWidth,
        buttonHeight
    };

    DrawText(titleText, (screenWidth - titleTextWidth) / 2, screenHeight * 0.40, titleFontSize, YELLOW);
    DrawText(welcomeText, (screenWidth - welcomeTextWidth) / 2, screenHeight * 0.5, welcomeFontSize, WHITE);
    DrawRectangleRec(button, LIGHTGRAY);
    DrawText(buttonText,
             button.x + (button.width - MeasureText(buttonText, buttonFontSize)) / 2,
             button.y + (button.height - buttonFontSize) / 2,
             buttonFontSize, BLACK);

    // Si le bouton est cliqué, retourner 1
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(GetMousePosition(), button)) {
        return 1;
        }

    return 0;
}
