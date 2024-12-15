#include "raylib.h"
#include "chicken.h"
#include <stdlib.h>
#include <time.h>

#include "userprofile.h"

#define GRID_SIZE 5        // Taille de la grille (5x5)
#define NUM_CHICKENS 20    // Nombre de poulets

void InitializeGameState(GameState* gameChicken) {
    gameChicken->bet = 100;
    gameChicken->multiplier = 0;
    gameChicken->gameStarted = true;
    // Initialisation de la grille 5x5 avec des positions et états par défaut
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            gameChicken->grid[i][j].x = i;  // Initialisation des positions
            gameChicken->grid[i][j].y = j;  // Initialisation des positions
            gameChicken->grid[i][j].isRevealed = false;
            gameChicken->grid[i][j].containsChicken = false;
        }
    }

    // Placer les poulets aléatoirement
    int chickensPlaced = 0;
    while (chickensPlaced < NUM_CHICKENS) {
        int randX = GetRandomValue(0, GRID_SIZE - 1);
        int randY = GetRandomValue(0, GRID_SIZE - 1);
        if (!gameChicken->grid[randX][randY].containsChicken) {
            gameChicken->grid[randX][randY].containsChicken = true;
            chickensPlaced++;
        }
    }
}

void UpdateGame(GameState* gameChicken) {
    // Vérifier si un clic de souris a été effectué
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();

        // Vérifier si le clic est dans une cellule non révélée
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                Rectangle cellRect = { gameChicken->grid[i][j].x * 100 + 145, gameChicken->grid[i][j].y * 100 + 90, 100, 100 };

                if (CheckCollisionPointRec(mousePos, cellRect) && !gameChicken->grid[i][j].isRevealed) {
                    // Révéler la case
                    gameChicken->grid[i][j].isRevealed = true;

                    // Vérifier si la case contient un poulet
                    if (gameChicken->grid[i][j].containsChicken) {
                        gameChicken->multiplier += 1;
                    } else {
                        // Si la case contient un os, la partie est perdue
                        gameChicken->gameStarted = false; // Fin du jeu
                    }
                }
            }
        }
    }

    // Vérifier si toutes les cases ont été révélées
    bool allRevealed = true;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (!gameChicken->grid[i][j].isRevealed) {
                allRevealed = false;
                break;
            }
        }
        if (!allRevealed) break;
    }

    if (allRevealed) {
        gameChicken->gameStarted = false;  // Partie terminée
    }
}

void DrawChicken(int screenWidth, int screenHeight, GameState* gameChicken, UserProfile* userProfile) {
    ClearBackground(DARKGREEN);

    if (!gameChicken->gameStarted) {
        // Afficher l'écran de fin
        DrawText("Partie finie !", 350, 200, 40, RED);
        DrawRectangle(350, 500, 100, 40, GREEN);  // Bouton REJOUER
        DrawText("REJOUER", 355, 510, 20, WHITE);

        // Attendre un clic pour rejouer ou revenir au menu
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            Rectangle retryButton = { 350, 500, 100, 40 };

            if (CheckCollisionPointRec(mousePos, retryButton)) {
                userProfile->tokens -= 100;
                SaveUserProfile(userProfile);
                InitializeGameState(gameChicken);  // Réinitialiser l'état du jeu
            }
        }
        return;
    }

    // Dessiner la grille 5x5
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            Color cellColor = gameChicken->grid[i][j].isRevealed ? LIGHTGRAY : DARKGRAY;

            // Dessiner chaque cellule
            DrawRectangle(gameChicken->grid[i][j].x * 100 + 145, gameChicken->grid[i][j].y * 100 + 90, 100, 100, cellColor);

            // Dessiner un texte pour chaque cellule révélée
            if (gameChicken->grid[i][j].isRevealed) {
                if (gameChicken->grid[i][j].containsChicken) {
                    DrawText("P", gameChicken->grid[i][j].x * 100 + 35 + 145, gameChicken->grid[i][j].y * 100 + 35 + 90, 30, RED);
                } else {
                    DrawText("O", gameChicken->grid[i][j].x * 100 + 35 + 145, gameChicken->grid[i][j].y * 100 + 35 + 90, 30, GRAY);
                }
            }
            DrawRectangleLines(gameChicken->grid[i][j].x * 100 + 145, gameChicken->grid[i][j].y * 100 + 90, 100, 100, BLACK);
        }
    }

    // Afficher la mise, le multiplicateur, et un bouton "Encaisser"
    DisplayUserBalance(userProfile);
    DrawText(TextFormat("Mise: %d", gameChicken->bet), 10, 40, 20, BLACK);
    DrawText(TextFormat("Multiplicateur: %d", gameChicken->multiplier), 10, 60, 20, BLACK);

    DrawRectangle(650, 10, 140, 40, GOLD);  // Bouton "Encaisser"
    DrawText("ENCAISSER", 660, 20, 20, BLACK);

    // Gérer le clic sur "Encaisser"
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        Rectangle cashoutButton = { 650, 10, 140, 40 };

        if (CheckCollisionPointRec(mousePos, cashoutButton)) {
            // Ajouter les gains au solde utilisateur
            int gains = gameChicken->bet * gameChicken->multiplier;
            userProfile->tokens += gains;
            SaveUserProfile(userProfile);
            // Fin de la partie
            gameChicken->gameStarted = false;


        }
    }
}

