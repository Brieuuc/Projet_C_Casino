#include <raylib.h>
#include "accueil.h"
#include "chicken.h"
#include "menu.h"

typedef enum {
    PAGE_ACCUEIL,
    PAGE_MENU,
    PAGE_JEU1,
    PAGE_JEU2,
    PAGE_JEU3
} Page;

int main() {
    int screenWidth = 800;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Brieuc's Casino");
    SetTargetFPS(60);

    Page currentPage = PAGE_ACCUEIL;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGREEN);

        switch (currentPage) {
            case PAGE_ACCUEIL:
                if (DrawAccueil(screenWidth, screenHeight)) {
                    currentPage = PAGE_MENU;
                }
                break;

            case PAGE_MENU:
                int selectedGame = DrawMenu(screenWidth, screenHeight);
                if (selectedGame == 1) {
                    currentPage = PAGE_JEU1;
                } else if (selectedGame == 2) {
                    currentPage = PAGE_JEU2;
                } else if (selectedGame == 3) {
                    currentPage = PAGE_JEU3;
                }
                break;

            case PAGE_JEU1:
                DrawText("Jeu 1 - Chicken Game", screenWidth / 2 - MeasureText("Jeu 1 - Chicken Game", 20) / 2, screenHeight / 2, 20, WHITE);
                // Appuyer sur BACKSPACE pour revenir au menu
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    currentPage = PAGE_MENU;
                }
                break;

            case PAGE_JEU2:
                currentPage = PAGE_MENU;
                break;

            case PAGE_JEU3:
                currentPage = PAGE_MENU;
                break;
        }

        // Gérer la fermeture de la fenêtre : si l'utilisateur presse BACKSPACE sur la page d'accueil ou du menu
        if (WindowShouldClose() && (currentPage == PAGE_ACCUEIL || currentPage == PAGE_MENU)) {
            break; // Fermer l'application si on est dans ces pages
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}