#include <raylib.h>
#include <stdio.h>
#include <math.h>

int main() {
    int screenWidth = 800;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Brieuc's Casino");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGREEN);

        // Affichage du titre
        DrawText("Brieuc's Casino", (screenWidth - MeasureText("Brieuc's Casino", 48)) / 2, (screenHeight - 200) / 2, 48, WHITE);
        DrawText("Bienvenue au casino !", (screenWidth - MeasureText("Bienvenue au casino !", 20)) / 2, (screenHeight - 20) / 2, 20, WHITE);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
