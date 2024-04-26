#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "joueur.h"

//plus tard pour l´amelioration du robot
void distribuerCartesRobot(Joueur *joueur, Carte paquet[], int *taillePaquet, int nombreDeCartes)
{
    for (int j = 0; j < nombreDeCartes; j++)
    {
        int carteAleatoire = rand() % (*taillePaquet);
        joueur->main[j] = paquet[carteAleatoire];

        // Retirer la carte du paquet
        paquet[carteAleatoire] = paquet[(*taillePaquet) - 1];
        (*taillePaquet)--;

        // Triez les cartes du joueur dans l'ordre croissant
        for (int k = 0; k < j; k++)
        {
            if (joueur->main[j].numero < joueur->main[k].numero)
            {
                Carte temp = joueur->main[j];
                joueur->main[j] = joueur->main[k];
                joueur->main[k] = temp;
            }
        }
    }
}


// affiche la main du joueur ou robot pour verifier leurs cartes
void afficherMain(Joueur joueur)
{
    printf("Main du joueur %s :\n", joueur.nom);
    for (int j = 0; j < 10; j++)
    {
        printf("%d :",j);
        afficherCarte(joueur.main[j]);
    }
}


//distribue les cartes non trié par ordre croissant
void distribuerCartes(Joueur *joueur, Carte paquet[], int *taillePaquet, int nombreDeCartes)
{
    for (int j = 0; j < nombreDeCartes; j++)
    {
        int carteAleatoire = rand() % (*taillePaquet);
        joueur->main[j] = paquet[carteAleatoire];

        // Retirer la carte du paquet
        paquet[carteAleatoire] = paquet[(*taillePaquet) - 1];
        (*taillePaquet)--;
    }
}


// distribue les cartes dans l ordre croissant pour le joueur
void distribuerCartesJoueur(Joueur *joueur, Carte paquet[], int *taillePaquet, int nombreDeCartes)
{
    for (int j = 0; j < nombreDeCartes; j++)
    {
        int carteAleatoire = rand() % (*taillePaquet);
        joueur->main[j] = paquet[carteAleatoire];

        // Retirer la carte du paquet
        paquet[carteAleatoire] = paquet[(*taillePaquet) - 1];
        (*taillePaquet)--;

        // Triez les cartes du joueur dans l'ordre croissant
        for (int k = 0; k < j; k++) {
            if (joueur->main[j].numero < joueur->main[k].numero)
            {
                Carte temp = joueur->main[j];
                joueur->main[j] = joueur->main[k];
                joueur->main[k] = temp;
            }
        }
    }
}


// selectionne une carte aleatoire dans la main du robot
int selectionnerCarteAleatoireRobot()
{
    // Générez un index aléatoire entre 0 et 9
    return rand() % 10;
}


// le joueur selectionne sa carte en tapant l'indice dans le terminal
int selectionnerCarteParSaisie(Joueur *joueur)
{
    int indexSelection = -1;

    // Demandez au joueur de sélectionner une carte tant qu'une entrée valide n'est pas fournie
    while (indexSelection < 0 || indexSelection >= 10 || (joueur->main[indexSelection].numero == 0 && joueur->main[indexSelection].valeur == 0))
    {
        printf(" entrez l'index de la carte que vous souhaitez sélectionner (de 0 à 9) : ");
        scanf("%d", &indexSelection);
    }

    return indexSelection;
}


int selectionnerCarteRobot(Carte table[][6], Carte main[])
{
    ResultatComparaison resultats[10]; // Tableau pour stocker les résultats de comparaison
    int indexSelection = -1; // Initialise l'index de sélection à -1

    // Initialisation des résultats avec des valeurs maximales
    for (int i = 0; i < 10; ++i)
    {
        resultats[i].indiceCarte = i;
        resultats[i].differenceMin = INT_MAX;
    }

    // Parcours de chaque carte dans la main du robot
    for (int i = 0; i < 10; ++i)
    {
        if (main[i].numero != 0)
        {
            // Parcours de chaque ligne dans la table
            for (int j = 0; j < 4; ++j)
            {
                if (table[j][0].numero != 0)
                {
                    int cartesSurLigne = 0;
                    for (int k = 0; k < 6; ++k)
                    {
                        if (table[j][k].numero != 0)
                        {
                            cartesSurLigne++;
                        }
                    }

                    if (cartesSurLigne != 5)
                    {
                        for (int k = 0; k < 6; ++k)
                        {
                            if (table[j][k].numero != 0)
                            {
                                int difference = main[i].numero - table[j][k].numero;
                                if (difference < 0)
                                {
                                    difference = 500; // Fixe la différence minimale à 500 si elle est négative
                                }

                                // Mise à jour de la différence minimale dans les résultats
                                if (difference < resultats[i].differenceMin)
                                {
                                    resultats[i].differenceMin = difference;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // Trie les résultats en fonction de la différence minimale (ordre croissant)
    for (int i = 0; i < 10 - 1; ++i)
    {
        for (int j = 0; j < 10 - i - 1; ++j)
        {
            if (resultats[j].differenceMin > resultats[j + 1].differenceMin)
            {
                // Échange des résultats si la différence est plus grande
                ResultatComparaison temp = resultats[j];
                resultats[j] = resultats[j + 1];
                resultats[j + 1] = temp;
            }
        }
    }

    // Récupère l'index de la carte à sélectionner (indice minimum)
    indexSelection = resultats[0].indiceCarte;

    return indexSelection; // Retourne l'index de la carte sélectionnée
}


void afficherListeJoueurs(Joueur joueurs[], int taille)
{
    for (int i = 0; i < taille; ++i)
    {
        printf("Joueur %d : %s\n", i + 1, joueurs[i].nom);
    }
}


void redistribuerCartes(Joueur joueurs[], int nombreJoueursTotal, Carte paquet[], int *taillePaquet)
{
    for (int i = 0; i < nombreJoueursTotal; i++)
    {
        distribuerCartes(&joueurs[i], paquet, taillePaquet, 10);
        afficherMain(joueurs[i]);
    }
}


// Fonction pour trouver le score maximum parmi les joueurs
int trouverScoreMax(Joueur joueurs[], int nombreJoueursTotal)
{
    int scoreMax = -1; // Initialisation avec une valeur basse possible

    for (int g = 0; g < nombreJoueursTotal; g++)
    {
        if (joueurs[g].scores > scoreMax)
        {
            scoreMax = joueurs[g].scores;
        }
    }
    return scoreMax;
}


// Fonction pour trouver le score maximum parmi les joueurs
void afficherClassement(Joueur joueurs[], int nombreJoueursTotal)
{
    // Création d'un tableau d'indices pour conserver l'ordre original des joueurs
    int classement[nombreJoueursTotal];

    // Initialisation du classement
    for (int i = 0; i < nombreJoueursTotal; i++)
    {
        classement[i] = i;
    }
    // Tri des joueurs selon leur score en utilisant l'algorithme du tri par sélection
    for (int i = 0; i < nombreJoueursTotal - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < nombreJoueursTotal; j++)
        {
            if (joueurs[classement[j]].scores < joueurs[classement[min]].scores)
            {
                min = j;
            }
        }
        // Échange des indices pour mettre le joueur avec le plus petit score en premier
        int temp = classement[min];
        classement[min] = classement[i];
        classement[i] = temp;
    }
    // Affichage du classement avec les scores
    printf("Classement des joueurs :\n");
    for (int i = 0; i < nombreJoueursTotal; i++)
    {
        printf("%d. Joueur %s - Score : %d\n", i + 1, joueurs[classement[i]].nom, joueurs[classement[i]].scores);
    }
}
