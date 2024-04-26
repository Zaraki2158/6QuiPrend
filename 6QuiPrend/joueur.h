#ifndef JOUEUR_H
#define JOUEUR_H
#include "carte.h"

// structure pour représenter un joueur (humain ou robot)
typedef struct
{
    char nom[50];
    Carte main[10]; // Main du joueur
    Carte selection[10]; // Cartes sélectionnées par le joueur
    int scores; // score joueur
}
Joueur;


typedef struct {
    int indiceCarte;
    int differenceMin;
} ResultatComparaison;

void selectionnerCarte(Joueur *joueur, int indexCarte);
void distribuerCartes(Joueur *joueur, Carte paquet[], int *taillePaquet, int nombreDeCartes);
void distribuerCartesJoueur(Joueur *joueur, Carte paquet[], int *taillePaquet, int nombreDeCartes);
void distribuerCartesRobot(Joueur *joueur, Carte paquet[], int *taillePaquet, int nombreDeCartes);
void afficherMain(Joueur joueur);
int selectionnerCarteAleatoireRobot();
int selectionnerCarteParSaisie(Joueur *joueur);
int selectionnerCarteRobot(Carte table[][6], Carte main[]);
void afficherListeJoueurs(Joueur joueurs[], int taille);
void redistribuerCartes(Joueur joueurs[], int nombreJoueursTotal, Carte paquet[], int *taillePaquet);
int trouverScoreMax(Joueur joueurs[], int nombreJoueursTotal);
void afficherClassement(Joueur joueurs[], int nombreJoueursTotal);
#endif // JOUEUR_H
