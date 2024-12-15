#include "raylib.h"
#include "userprofile.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Fonction pour initialiser ou charger le profil utilisateur
void InitializeOrLoadUserProfile(UserProfile* profile) {
    FILE* file = fopen(PROFILE_FILE, "rb");
    if (file == NULL) {
        printf("Fichier utilisateur non trouvé. Création d'un nouveau profil.\n");
        // Création d'un nouveau profil
        strncpy(profile->name, "Joueur", MAX_NAME_LENGTH);
        profile->tokens = 200;
        profile->gamesPlayed = 0;
        SaveUserProfile(profile);  // Sauvegarder le nouveau profil
    } else {
        // Chargement des données existantes
        fread(profile, sizeof(UserProfile), 1, file);
        fclose(file);
        printf("Profil chargé : %s, %d jetons.\n", profile->name, profile->tokens);
    }
}


// Fonction pour sauvegarder le profil dans un fichier
void SaveUserProfile(const UserProfile* profile) {
    FILE* file = fopen(PROFILE_FILE, "wb");
    if (file != NULL) {
        fwrite(profile, sizeof(UserProfile), 1, file);
        fclose(file);
    }
}

// Fonction pour afficher le solde des jetons
void DisplayUserBalance(UserProfile* profile) {
    // Afficher le solde des jetons en haut à gauche
    DrawText(TextFormat("Solde: %d", profile->tokens), 10, 10, 20, BLACK);
}

int DisplayStats(UserProfile* userProfile) {
    DrawText("Statistiques", 240, 100, 50, BLACK);
    DrawText("NOM", 350, 200, 25, WHITE);
    DrawText("Joueur", 350, 230, 20, WHITE);
    DrawText("Parties jouées", 280, 260, 25, WHITE);
    DrawText(TextFormat("%d", userProfile->gamesPlayed), 365, 300, 20, WHITE);
    // Retour
    DrawRectangle(330, 360, 100, 40, GREEN);
    DrawText("RETOUR", 335, 370, 20, WHITE);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        Rectangle backButton = { 350, 360, 100, 40 };
        if (CheckCollisionPointRec(mousePos, backButton)) {
            return 1;
        }
    }

    return 0;
}