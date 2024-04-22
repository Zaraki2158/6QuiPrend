#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "gestionjeu.h"


//pose les cartes sur "la table"
void poserCartesSurTable(Carte table[][6], Carte paquet[], int nombreDeCartes)
{
    for (int i = 0; i < nombreDeCartes; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (table[j][0].valeur == 0)
            {
                table[j][0] = paquet[i];
                break;
            }
        }
    }
}

//affiche le jeu en cours
void afficherTable(Carte table[][6])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            printf("(%d, %d) ", table[i][j].numero, table[i][j].valeur);
        }
        printf("\n");
    }
}

//affiche les cartes selectionne pour ce tours
void afficherCarteSelectionnee(Carte tableau[],int taille)
{
    printf("Carte selectionnée par le(s) joueur(s) et le(s) robot(s)");
        for (int i = 0; i < taille; i++)
    {
        printf("(%d, %d) ", tableau[i].numero, tableau[i].valeur);
    }
    printf("\n\n");
}


int scores[10] = {0}; // Tableau pour stocker les scores de chaque joueur

void ajouterCartesAuTable(Carte table[][6], Carte cartes[], Joueur joueurs[10], int taille)
{

    for (int i = 0; i < taille; i++)
    {
        int p = 0; // score du joueur pour les lignes récupérées
        int p1 = 0; // score du joueur pour les lignes supprimées
        int ligneLaPlusProche = -1; // Initialise l'index de la ligne la plus proche à -1
        int differenceMin = -1; // Initialise la différence minimale à -1
        int ligneARecuperer = -1; // Initialise l'index de la ligne à récupérer à -1
        int valeurMin = -1; // Initialise la valeur minimale à -1
        int ligneAEnlever = -1; // Initialise l'index de la ligne à enlever à -1

        // Parcours des lignes de la table
        for (int j = 0; j < 4; j++)
        {
            int dernierNumero = -1; // Initialise le numéro de la dernière carte à -1

            // Parcours des emplacements dans chaque ligne
            for (int k = 0; k < 6; k++)
            {
                if (table[j][k].numero != 0)
                {
                    dernierNumero = table[j][k].numero; // Met à jour le dernier numéro si la case n'est pas vide
                }
                else
                {
                    break; // Sort de la boucle si la case est vide
                }
            }

            if (dernierNumero != -1)
            {
                int difference = cartes[i].numero - dernierNumero; // Calcule la différence
                if ((ligneLaPlusProche == -1 || difference < differenceMin) && difference >= 0)
                {
                    ligneLaPlusProche = j; // Met à jour l'index de la ligne la plus proche si une meilleure ligne est trouvée
                    differenceMin = difference; // Met à jour la différence minimale
                }

                // Calcule la valeur additionnée de la rangée
                int valeurRangee = 0;
                    for (int k = 0; k < 6; k++)
                {
                    valeurRangee += table[j][k].valeur;
                }

                if (cartes[i].numero < dernierNumero)
                {
                    if (ligneARecuperer == -1 || valeurRangee < valeurMin)
                    {
                        ligneARecuperer = j; // Met à jour l'index de la ligne à récupérer si la condition est remplie
                        valeurMin = valeurRangee; // Met à jour la valeur minimale
                    }
                }

                // Vérifie si la ligne a déjà 5 cartes
                int cartesDansLaLigne = 0;
                for (int k = 0; k < 6; k++)
                {
                    if (table[j][k].numero != 0)
                    {
                        cartesDansLaLigne++;
                    }
                }
                if (cartesDansLaLigne == 5)
                {
                    // Si la différence minimale est sur cette ligne, marquez-la pour suppression
                    if (j == ligneLaPlusProche)
                    {
                        ligneAEnlever = j;
                    }
                }
            }
        }

        if (ligneAEnlever != -1)
        {
            // Vérifie si la cinquième carte a la différence minimale
            int differenceCinquiemeCarte = cartes[i].numero - table[ligneAEnlever][4].numero;
            if (differenceCinquiemeCarte == differenceMin)
            {
                // Supprime la ligne en ajoutant des zéros
                for (int k = 0; k < 6; k++)
                {
                     //printf("valeur carte a %d\n", table[ligneAEnlever][k].valeur);
                    p1 =p1+table[ligneAEnlever][k].valeur;
                    table[ligneAEnlever][k].numero = 0;
                    table[ligneAEnlever][k].valeur = 0;
                }
                printf("Le joueur %s a recuperé %d têtes de bœuf car sa carte avait la difference minimum avec une ligne possedant deja 5 cartes\n\n", joueurs[i].nom, p1);
            }
        }
        if (ligneLaPlusProche != -1)
        {
            for (int k = 0; k < 6; k++)
            {
                if (table[ligneLaPlusProche][k].numero == 0)
                {
                    table[ligneLaPlusProche][k] = cartes[i]; // Place la carte sélectionnée dans la première case vide de la ligne la plus proche
                    break; // Sort de la boucle
                }
            }
        }
        else if (ligneARecuperer != -1)
        {
            // Le joueur récupère la rangée entière et remplace la première ligne par sa carte
            for (int k = 0; k < 6; k++)
            {
                //point(table[ligneARecuperer][k].valeur);
                p =p+table[ligneARecuperer][k].valeur;

                table[ligneARecuperer][k].numero = 0; // Met à jour le numéro à zéro pour supprimer la ligne
                table[ligneARecuperer][k].valeur = 0; // Met à jour la valeur à zéro
            }
            table[ligneARecuperer][0] = cartes[i]; // Place la carte du joueur dans la première ligne de la rangée récupérée
             printf("Le joueur %s a recuperé %d têtes de bœuf car aucune ligne n'avait une valeur plus petit que sa carte.\n\n", joueurs[i].nom, p);
            //joueurs[i].score=p;
        }
        // Ajout des scores pour ce tour au score total du joueur
        int totalScore = p + p1;
        joueurs[i].scores += totalScore;

        // Affichage du score total pour ce tour
        printf("Le joueur %s a un total de %d têtes de bœuf pour ce tour.\n", joueurs[i].nom, joueurs[i].scores);
    }

}

//trie les cartes du joueurs par ordre croissqnt et trie les joueurs dans le mem ordres que les cartes
void trierCartesEtJoueurs(Carte cartes[], Joueur joueurs[], int taille) {
    for (int i = 1; i < taille; i++) {
        Carte cle = cartes[i];
        Joueur joueurCle = joueurs[i];
        int j = i - 1;

        while (j >= 0 && cartes[j].numero > cle.numero) {
            cartes[j + 1] = cartes[j];
            joueurs[j + 1] = joueurs[j];
            j = j - 1;
        }

        cartes[j + 1] = cle;
        joueurs[j + 1] = joueurCle;
    }
}

//trie les cartes dans l ordre croissant
void trierCartes(Carte cartes[], int taille) {
    for (int i = 1; i < taille; i++) {
        Carte cle = cartes[i];
        int j = i - 1;

        while (j >= 0 && cartes[j].numero > cle.numero) {
            cartes[j + 1] = cartes[j];
            j = j - 1;
        }

        cartes[j + 1] = cle;
    }
}

//selectionne la carte pour le joueur et la met a 0
void selectionnerCarte(Joueur *joueur, int indexCarte)
{
    if (indexCarte >= 0 && indexCarte < 10)
    {
        joueur->selection[indexCarte] = joueur->main[indexCarte];
        joueur->main[indexCarte].numero = 0;
        joueur->main[indexCarte].valeur = 0;
    }
}
