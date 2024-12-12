#ifndef USERPROFILE_H
#define USERPROFILE_H

#define MAX_NAME_LENGTH 50
#define PROFILE_FILE "userprofile.dat"  // Nom du fichier de sauvegarde du profil

typedef struct {
    char name[MAX_NAME_LENGTH];  // Nom du joueur
    int tokens;                  // Nombre de jetons
    int gamesPlayed;             // Nombre de jeux joués
    int gamesWon;                // Nombre de jeux gagnés
    int gamesLost;               // Nombre de jeux perdus
} UserProfile;

// Initialiser ou charger le profil utilisateur
void InitializeOrLoadUserProfile(UserProfile* profile);

// Sauvegarder le profil utilisateur dans un fichier
void SaveUserProfile(const UserProfile* profile);

// Afficher le solde des jetons
void DisplayUserBalance(UserProfile* profile);

#endif