#ifndef CHICKEN_H
#define CHICKEN_H

#define GRID_SIZE 5
#include "userprofile.h"

typedef struct Cell {
    int x;
    int y;
    bool isRevealed;
    bool containsChicken;
} Cell;

typedef struct gameStateChicken {
    int bet;
    int multiplier;
    Cell grid[GRID_SIZE][GRID_SIZE];
    bool gameStarted;
    bool isGameIntro;
} GameState;

void InitializeGameState(GameState* gameChicken);
void UpdateGame(GameState* gameChicken);
void DrawChicken(int screenWidth, int screenHeight, GameState* gameChicken, UserProfile* userProfile);


#endif
