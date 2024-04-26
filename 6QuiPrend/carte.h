#ifndef CARTE_H
#define CARTE_H

// structure carte nous permet de stocker le numero et la valeur de la carte
typedef struct
{
    int numero;
    int valeur;
}
Carte;


void creerPaquetDeCartes(Carte paquet[]);
void afficherPaquetDeCartes(Carte paquet[], int taille);
void melangePaquet(Carte paquet[], int taille);
void afficherCarte(Carte carte);
void retirerCartesDuPaquet(Carte paquet[], int *taillePaquet, Carte cartesARetirer[][6], int nombreDeCartes);

#endif // CARTE_H
