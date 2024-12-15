#include <raylib.h>
#include <stdlib.h>
#include "accueil.h"
#include "chicken.h"
#include "menu.h"
#include "userprofile.h"

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

    UserProfile userProfile;
    InitializeOrLoadUserProfile(&userProfile);  // Charger ou créer un profil utilisateur


    // Pointeur vers l'état du jeu
    GameState* chickenGameState = NULL;
    bool gameStarted = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGREEN);
        DisplayUserBalance(&userProfile);
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
                }
                break;

            case PAGE_JEU1:
                if (!gameStarted) {
                    // Allouer dynamiquement la mémoire pour GameState
                    chickenGameState = (GameState*)malloc(sizeof(GameState));
                    if (chickenGameState != NULL) {
                        userProfile.tokens -= 100;
                        SaveUserProfile(&userProfile);
                        InitializeGameState(chickenGameState); // Initialiser l'état du jeu
                        gameStarted = true;
                    }
                }
                if (chickenGameState != NULL) {
                    if (!chickenGameState->gameStarted) {
                        DrawChicken(screenWidth, screenHeight, chickenGameState, &userProfile);
                    } else {
                        UpdateGame(chickenGameState); // Mettre à jour l'état du jeu
                        DrawChicken(screenWidth, screenHeight, chickenGameState, &userProfile);
                    }
                }
            break;

        }

        EndDrawing();
    }

    CloseWindow(); // Fermer la fenêtre
    return 0;
}
