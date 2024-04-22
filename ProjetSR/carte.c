#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "carte.h"


// creer un paquet de carte avec les valeur(tete de boeuf) associé a la carte
void creerPaquetDeCartes(Carte paquet[])
{
    for (int i = 0; i < 104; i++)
    {
        // carte 10,20,30,40....
        paquet[i].numero = i + 1;
        if ((i + 1) % 5 == 0)
        {
            if ((i + 1) % 2 == 0)
            {
                paquet[i].valeur = 3;
            }
            else
            {
                // carte 55
                if (i == 54)
                {
                    paquet[i].valeur = 7;
                    // carte 15,25,35,45...
                }
                else
                {
                    paquet[i].valeur = 2;
                }
            }
            //carte 11,22,33,44...
        }
        else if ((i + 1) % 11 == 0)
        {
            paquet[i].valeur = 5;
            //toutes les autres cartes
        }
        else
        {
            paquet[i].valeur = 1;
        }
    }
}


//affiche le paquet de carte pour verifier si il est bien melangé
void afficherPaquetDeCartes(Carte paquet[], int taille)
{
    for (int i = 0; i < taille; i++)
    {
        printf("%d: Carte numero %d, valeur %d\n",i+1, paquet[i].numero, paquet[i].valeur);
    }
}


// melange notre paquet de carte
void melangePaquet(Carte paquet[], int taille)
{


    // Mélanger le paquet en permutant aléatoirement les cartes
    for (int i = taille - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Carte temp = paquet[i];
        paquet[i] = paquet[j];
        paquet[j] = temp;
    }
}


//affiche les cartes selectionner par le joueur et le robot
void afficherCarte(Carte carte)
{
    printf("(%d, %d)\n", carte.numero, carte.valeur);
}


// retire les cartes du paquets
void retirerCartesDuPaquet(Carte paquet[], int *taillePaquet, Carte cartesARetirer[][6], int nombreDeCartes)
{
    for (int i = 0; i < nombreDeCartes; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            for (int k = 0; k < *taillePaquet; k++)
            {
                if (paquet[k].numero == cartesARetirer[i][j].numero)
                {
                    paquet[k] = paquet[(*taillePaquet) - 1];
                    (*taillePaquet)--;
                    break;
                }
            }
        }
    }
}



