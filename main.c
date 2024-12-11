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
                    if (!gameStarted) {
                        // Allouer dynamiquement la mémoire pour GameState
                        chickenGameState = (GameState*)malloc(sizeof(GameState));
                        if (chickenGameState != NULL) {
                            InitializeGameState(chickenGameState); // Initialiser l'état du jeu
                            gameStarted = true;
                        }
                    }
                } else if (selectedGame == 2) {
                    currentPage = PAGE_MENU;
                } else if (selectedGame == 3) {
                    currentPage = PAGE_MENU;
                }
                break;

            case PAGE_JEU1:
                if (chickenGameState != NULL) {
                    UpdateGame(chickenGameState); // Mettre à jour l'état du jeu à chaque frame
                    DrawChicken(screenWidth, screenHeight, chickenGameState); // Dessiner le jeu

                    // Si la partie est terminée, réinitialiser le jeu
                    if (!chickenGameState->gameStarted) {
                        // Le joueur a perdu ou a terminé la grille, donc on redémarre le jeu
                        currentPage = PAGE_MENU;
                        gameStarted = false;  // Arrêter le jeu

                        // Libérer la mémoire allouée pour GameState
                        free(chickenGameState);
                        chickenGameState = NULL; // Réinitialiser le pointeur
                    }
                }
                break;

            case PAGE_JEU2:
                break;

            case PAGE_JEU3:
                break;
        }

        EndDrawing();
    }

    CloseWindow(); // Fermer la fenêtre
    return 0;
}
