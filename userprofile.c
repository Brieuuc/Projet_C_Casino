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
        profile->gamesWon = 0;
        profile->gamesLost = 0;

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
