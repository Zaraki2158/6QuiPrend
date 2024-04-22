#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "gestionjeu.h"
//#include "joueur.h"
#include "jeu.h"

#define MAX_JOUEURS_TOTAL 10
#define MAX_CARTES_SELECTIONNEES (MAX_JOUEURS_TOTAL * 2)



void sauvegarderScores(int numeroManche, char nomJoueur[], int score)
{
    char commande[200]; // Augmentons la taille de la chaîne de commande pour plus de sécurité

    // Utilisation de sprintf pour générer la commande complète avec les valeurs des variables
    sprintf(commande, "awk -v nm=%d -v nj='%s' -v sc=%d 'BEGIN {print \"MANCHE : \" nm \", JOUEUR : \" nj \", SCORE : \" sc}' >> scores.log", numeroManche, nomJoueur, score);

    // Exécution de la commande via system()
    system(commande);
}

//convertie le fichier scores.log en fichier pdf grace a la librairie wkhtmltopdf qui doit etre installer sur l ordi avec-> sudo apt install wkhtmltopdf
void convertToPDF()
{
    system("wkhtmltopdf scores.log scores.pdf");
}


void swap(Joueur *a, Joueur *b)
{
    Joueur temp = *a;
    *a = *b;
    *b = temp;
}

//trie les joueurs dans l ordre croissant de leur scores a la fin de la parite
void trierJoueurs(Joueur joueurs[], int nombreJoueursTotal)
{
    int i, j;
    for (i = 0; i < nombreJoueursTotal - 1; i++)
    {
        for (j = 0; j < nombreJoueursTotal - i - 1; j++)
        {
            if (joueurs[j].scores > joueurs[j + 1].scores)
            {
                swap(&joueurs[j], &joueurs[j + 1]);
            }
        }
    }
}

//ecrit dans le fichier scores.log les scores des joueurs a chaque manches et le scores finale de chaque joueurs
void ecrireClassementDansFichier(Joueur joueurs[], int nombreJoueursTotal)
{
    trierJoueurs(joueurs, nombreJoueursTotal);

    FILE *fichierScores;
    fichierScores = fopen("scores.log", "a");

    if (fichierScores == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier des scores.\n");
        return;
    }

    fprintf(fichierScores, "Classement des joueurs :\n");
    for (int i = 0; i < nombreJoueursTotal; i++)
    {
        fprintf(fichierScores, "%d. Joueur %s - Score : %d\n", i + 1, joueurs[i].nom, joueurs[i].scores);
    }

    fclose(fichierScores);
}


void jeu()
{
    srand(time(NULL));
    int boeuf=66;

    int nombreJoueursTotal, nombreJoueursReels, difficulte;

    printf("Entrez le nombre de joueurs total (maximum 10) : ");
    scanf("%d", &nombreJoueursTotal);

    // Vérifier la limite pour le nombre total de joueurs
    if(nombreJoueursTotal > MAX_JOUEURS_TOTAL)
    {
        printf("Nombre total de joueurs depasse la limite de 10.\n");
        return;
    }


    printf("Entrez le nombre de joueurs reels (humains) parmi %d joueurs : ", nombreJoueursTotal);
    scanf("%d", &nombreJoueursReels);

    // Vérifier la limite pour le nombre de joueurs réels
    if(nombreJoueursReels > nombreJoueursTotal)
    {
        printf("Nombre de joueurs reels dépasse le nombre total de joueurs.\n");
        return;
    }


    printf("Avec combien de tetes de beoufs voulez vous jouer ?\n");
    scanf("%d", &boeuf);

    // Vérifier la limite pour le nombre de joueurs réels
    if(1 >boeuf || boeuf>120)
    {
        printf("Il y a trop de tete de boeuf.\n");
        return;
    }

    printf("Contre quelle dificultee de robot voulez vous jouer ?\nRobot aleatoire tapez: 1.\nRobot intelligent tapez:2.\n");
    scanf("%d", &difficulte);

    // Vérifier la limite pour le nombre de joueurs réels
    if(3 <= difficulte)
    {
        printf("Vous avez rentree une valeur incorrect.\n");
        return;
    }



    int nombreJoueursRobots = nombreJoueursTotal - nombreJoueursReels;

    Joueur joueurs[MAX_JOUEURS_TOTAL];
    Carte paquet[104];
    // Initialisation du tableau de cartes à 0
    Carte table[4][6];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            table[i][j].numero = 0;
            table[i][j].valeur = 0;
        }
    }

    int taillePaquet = sizeof(paquet) / sizeof(paquet[0]);

    creerPaquetDeCartes(paquet);

    //test affichage
    printf("Paquet de cartes avant le melange :\n");
    afficherPaquetDeCartes(paquet, taillePaquet);

    melangePaquet(paquet, taillePaquet);

    //test affichage apres melangr
    printf("\nPaquet de cartes apres le melange :\n");
    afficherPaquetDeCartes(paquet, taillePaquet);

    // Poser 4 cartes sur la table
    poserCartesSurTable(table, paquet, 4);

    afficherTable(table);

    // Retirer les cartes de la table du paquet
    retirerCartesDuPaquet(paquet, &taillePaquet, table, 4);

    int indexJoueur = 0;

    for (int i = 0; i < nombreJoueursReels; i++)
    {
        Joueur nouveauJoueur;
        char nomJoueur[50];
        printf("Entrez le nom du joueur reel %d : \n", i + 1);
        fflush(stdout);
        scanf("%s", nomJoueur);
        strcpy(nouveauJoueur.nom, nomJoueur);

        distribuerCartes(&nouveauJoueur, paquet, &taillePaquet, 10);
        joueurs[indexJoueur++] = nouveauJoueur;
        //afficherMain(nouveauJoueur);
    }

    for (int i = 0; i < nombreJoueursRobots; i++)
    {
        Joueur nouveauRobot;
        char nomRobot[50];
        sprintf(nomRobot, "Robot%d", i + 1);
        strcpy(nouveauRobot.nom, nomRobot);

        distribuerCartes(&nouveauRobot, paquet, &taillePaquet, 10);
        joueurs[indexJoueur++] = nouveauRobot;
        //afficherMain(nouveauRobot);
    }


    Carte cartesSelectionnees[nombreJoueursTotal];


    // Initialisation des scores de chaque joueur à zéro
    for (int i = 0; i < nombreJoueursTotal; i++)
    {
      // Boucle pour initialiser chaque score à zéro
        for (int j = 0; j < 10; j++)
        {
            joueurs[i].scores = 0;
        }
    }
    int scoremax=0;
    int t=1;

    while(scoremax<boeuf)
    {
        printf("MANCHE : %d \n", t);
        int k=1;
        while (k<11 && scoremax<boeuf)
        {
            printf("TOUR : %d \n", k);
            // pour jouer seul sans voir les cartes des autres
            //afficherMain(joueurs[0]);
            // Affichage des mains avant la sélection des cartes
            for (int j = 0; j < nombreJoueursTotal; j++)
            {
                printf("Main de %s avant selection :\n", joueurs[j].nom);
                afficherMain(joueurs[j]);
            }
             // Sélection des cartes
            for (int j = 0; j < nombreJoueursTotal; j++)
            {
                int indexSelectionJoueur;
                if (j < nombreJoueursReels)
                {
                    // Pour les joueurs humains, sélection par saisie
                    indexSelectionJoueur = selectionnerCarteParSaisie(joueurs);
                    while (indexSelectionJoueur >= 0 && indexSelectionJoueur < 10 && joueurs[j].main[indexSelectionJoueur].numero == 0)
                    {
                        indexSelectionJoueur = selectionnerCarteParSaisie(joueurs);
                    }
                }
                else
                {
                    if(difficulte==2)
                    {
                        // Pour les joueurs robots, sélection aléatoire
                        indexSelectionJoueur = selectionnerCarteRobot(table, joueurs[j].main);
                    }
                    else
                    {
                        indexSelectionJoueur = selectionnerCarteAleatoireRobot();
                    }
                    while (indexSelectionJoueur >= 0 && indexSelectionJoueur < 10 && joueurs[j].main[indexSelectionJoueur].numero == 0)
                    {
                        if(difficulte==2)
                        {
                            // Pour les joueurs robots, sélection aléatoire
                            indexSelectionJoueur = selectionnerCarteRobot(table, joueurs[j].main);
                        }
                        else
                        {
                            indexSelectionJoueur = selectionnerCarteAleatoireRobot();
                        }
                    }
                }
                if (indexSelectionJoueur >= 0 && indexSelectionJoueur < 10)
                {
                    cartesSelectionnees[j] = joueurs[j].main[indexSelectionJoueur];
                    selectionnerCarte(&joueurs[j], indexSelectionJoueur);
                    printf("Carte sélectionnee pour %s :\n", joueurs[j].nom);
                    afficherCarte(cartesSelectionnees[j]);
                    //printf("Affichage de la main de %s après la sélection :\n", joueurs[j].nom);
                    //afficherMain(joueurs[j]);
                }
            }
            trierCartes(cartesSelectionnees,nombreJoueursTotal);
            //trierCartesEtJoueurs(cartesSelectionnees, joueurs, nombreJoueursTotal); // Tri des cartes et des joueurs
            printf("Liste des joueurs pour le tour %d :\n", k);
            afficherListeJoueurs(joueurs, nombreJoueursTotal);
            afficherCarteSelectionnee(cartesSelectionnees,  nombreJoueursTotal);
            ajouterCartesAuTable(table, cartesSelectionnees,joueurs, nombreJoueursTotal);
            afficherTable(table);

            // Réinitialisation pour le prochain tour
            memset(cartesSelectionnees, 0, sizeof(cartesSelectionnees));
            scoremax = trouverScoreMax(joueurs,nombreJoueursTotal);

            printf("FIN DU TOUR : %d \n\n", k);
            k++;
        }
        for(int g=0; g<nombreJoueursTotal; g++)
        {
            sauvegarderScores(t,joueurs[g].nom,joueurs[g].scores);
            printf("Le joueur %s a un total de %d têtes de bœuf pour la fin de cette manche.\n", joueurs[g].nom, joueurs[g].scores);
        }
        if(scoremax<boeuf)
        {
            printf("\nPaquet de cartes apres avoir retire les cartes de la table :\n");
            afficherPaquetDeCartes(paquet, taillePaquet);
            printf("FIN MANCHE : %d \n\n", t);
            t++;
            printf("\nMANCHE : %d \n", t);

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    table[i][j].numero = 0;
                    table[i][j].valeur = 0;
                }
            }

            int taillePaquet = sizeof(paquet) / sizeof(paquet[0]);

            creerPaquetDeCartes(paquet);

            //test affichage
            printf("Paquet de cartes avant le melange :\n");
            afficherPaquetDeCartes(paquet, taillePaquet);

            melangePaquet(paquet, taillePaquet);


            //test affichage apres melangr
            printf("\nPaquet de cartes apres le melange :\n");
            afficherPaquetDeCartes(paquet, taillePaquet);

            // Poser 4 cartes sur la table
            poserCartesSurTable(table, paquet, 4);

            afficherTable(table);

            // Retirer les cartes de la table du paquet
            retirerCartesDuPaquet(paquet, &taillePaquet, table, 4);


            // Redistribuer les cartes aux joueurs existants
            redistribuerCartes(joueurs, nombreJoueursTotal, paquet, &taillePaquet);
        }
    }
    afficherClassement(joueurs, nombreJoueursTotal);
    ecrireClassementDansFichier(joueurs,nombreJoueursTotal);
    convertToPDF();
    printf("Appuyez sur une touche pour quitter...");
    getchar(); // Attend une entrée de l'utilisateur
     getchar();
}
