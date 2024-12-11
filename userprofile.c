#include "raylib.h"
#include "userprofile.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Fonction pour initialiser ou charger le profil utilisateur
void InitializeOrLoadUserProfile(UserProfile* profile) {
    FILE* file = fopen(PROFILE_FILE, "rb");
    if (file == NULL) {
        // Si le fichier n'existe pas, on crée un nouveau profil avec des valeurs par défaut
        strncpy(profile->name, "Joueur", MAX_NAME_LENGTH);
        profile->tokens = 200;    // Valeur par défaut des jetons
        profile->gamesPlayed = 0;
        profile->gamesWon = 0;
        profile->gamesLost = 0;

        // Sauvegarder le profil initialisé dans un fichier
        SaveUserProfile(profile);
    } else {
        // Si le fichier existe, on charge les données
        fread(profile, sizeof(UserProfile), 1, file);
        fclose(file);
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
