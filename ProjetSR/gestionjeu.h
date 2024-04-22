#ifndef GESTIONJEU_H
#define GESTIONJEU_H
#include "carte.h"
#include "joueur.h"

void poserCartesSurTable(Carte table[][6], Carte paquet[], int nombreDeCartes);
void afficherTable(Carte table[][6]);
void trierCartes(Carte cartes[], int taille);
void ajouterCartesAuTable(Carte table[][6], Carte cartes[], Joueur joueurs[10], int taille);
void afficherCarteSelectionnee(Carte tableau[],int taille);
void trierCartesEtJoueurs(Carte cartes[], Joueur joueurs[], int taille);
void trierCartes(Carte cartes[], int taille);

#endif
