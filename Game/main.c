#include <stdio.h>
#include <stdlib.h>
#include "tron.h"

int main()
{
    tron();
    return 0;
}
/*
typedef struct Plateau
{
    int lignes;
    int colonnes;
    char** grille;
} Plateau;

typedef struct Joueur
{
    int colonne;
    int ligne;
    int victoires;
    char pion;
} Joueur;

Plateau* creer_plateau(int lignes, int colonnes);
Joueur* creer_joueur(char pions);
void afficher_plateau(Plateau* plateau);
void pos_initial(Joueur* joueur, int nombre, Plateau* plateau);
int defaite(Joueur* joueur[2], Plateau* plateau,int tour);
void initialiser_plateau(Plateau* plateau);
void affichage(Joueur* joueur[2], Plateau* plateau, int tour);
void affichage_defaite(Joueur* joueur[2], int tour);
void obtenir_entree(Joueur* joueur[2],int tour);
void positionner_pion(Joueur* joueur[2], Plateau* plateau,int tour);
void attribution_point(Joueur* joueur[2],int tour);
void affichage_point(Joueur* joueur[2]);
void detruire_plateau(Plateau** adr_plateau);
void detruire_joueurs(Joueur** adr_joueur);

int main()
{
    char rejouer;
    int tour = 0;
    Joueur* joueurs[2];
    joueurs[0] = creer_joueur('A');
    joueurs[1] = creer_joueur('X');
    Plateau* plateau = creer_plateau(21, 21);
    do
    {
        tour = 0;
        initialiser_plateau(plateau);
        pos_initial(joueurs[0], 6, plateau);
        pos_initial(joueurs[1], 14, plateau);
        do
        {
            affichage(joueurs, plateau, tour);
            obtenir_entree(joueurs, tour);
            if (!defaite(joueurs, plateau, tour))
            {
                positionner_pion(joueurs, plateau, tour);
            }
            else
            {
                affichage_defaite(joueurs, tour);
                break;
            }
            tour ++;
        }while(1);
        attribution_point(joueurs, tour);
        do
        {
            printf("voulez vous rejouer ? (Y/N)");
            scanf(" %c", &rejouer);
        }while (rejouer != 'Y' && rejouer != 'N');
    }while (rejouer == 'Y');
    detruire_plateau(&plateau);
    detruire_joueurs(&joueurs[0]);
    detruire_joueurs(&joueurs[1]);
    return 0;
}

Plateau* creer_plateau(int lignes, int colonnes)
{
    Plateau* plateau = malloc(sizeof(Plateau));
    plateau -> lignes = lignes;
    plateau -> colonnes = colonnes;
    plateau -> grille = malloc(lignes * sizeof(char*) );
    for(int i = 0; i < lignes; i++)
    {
        plateau -> grille[i] = malloc(colonnes * sizeof(char));
        for(int n = 0; n < colonnes; n++)
        {
            plateau -> grille[i][n] = '.';
        }
    }
    return plateau;
}

Joueur* creer_joueur(char pions)
{
    Joueur* joueur = malloc(sizeof(Joueur));
    joueur->pion = pions;
    joueur->victoires = 0;
    joueur->ligne = 11;
    return joueur;
}

void afficher_plateau(Plateau* plateau)
{
    for(int i = 0; i < plateau->lignes; i++)
    {
        for(int n = 0; n < plateau->colonnes; n++)
        {
            gotoxy(n*2+18,i+6);
            switch(plateau -> grille[i][n])
            {
            case '.':
                printf(".");
                break;
            case 'A':
                textcolor(LIGHTCYAN);
                printf("%c", (char)254);
                break;
            case 'X':
                textcolor(LIGHTRED);
                printf("%c", (char)254);
                break;
            }
            textcolor(WHITE);
        }
    }
}

void pos_initial(Joueur* joueur, int nombre, Plateau* plateau)
{
    plateau->grille[10][nombre] = joueur->pion;
    joueur->colonne = nombre;
    joueur->ligne = 10;

}

int defaite(Joueur* joueur[2], Plateau* plateau,int tour)
{
    if (joueur[tour%2]->ligne == -1 ||
        joueur[tour%2]->ligne == 21 ||
        joueur[tour%2]->colonne == -1 ||
        joueur[tour%2]->colonne == 21)
    {
        return 1;
    }
    else
    {
        if(plateau->grille[joueur[tour%2]->ligne][joueur[tour%2]->colonne] != '.')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

 void initialiser_plateau(Plateau* plateau)
 {
     int i,j;
     for (i = 0; i < plateau->colonnes; i++)
     {
         for (j = 0; j < plateau->lignes; j++)
         {
             plateau->grille[i][j] = '.';
         }
     }
 }

void affichage(Joueur* joueur[2], Plateau* plateau, int tour)
{
    textcolor(YELLOW);
    gotoxy(29, 3);
    printf("Les Pietons de tron");
    afficher_plateau(plateau);
    affichage_point(joueur);
    gotoxy(1,27);
    printf("Tour %d", tour+1);
    gotoxy(1,28);
    if (tour%2 == 0)
    {
        textcolor(LIGHTCYAN);
    }
    else
    {
        textcolor(LIGHTRED);
    }
    printf("C'est au joueur %d de jouer.", tour%2+1);
    textcolor(WHITE);
}

void affichage_defaite(Joueur* joueur[2], int tour)
{
    gotoxy(1,31);
    printf("Joueur %d a perdu.", tour%2+1);
}

void obtenir_entree(Joueur* joueur[2],int tour)
{
    char direction;
    gotoxy(1,29);
    do
    {
        printf("Ou veux-tu aller ?(N/S/E/W)\n");
        scanf(" %c", &direction);
        printf("\n");
    }while (direction != 'N' && direction != 'S' && direction != 'E' && direction != 'W');
    clrscr();
    switch(direction)
    {
    case'N':
        joueur[tour%2]->ligne --;
        break;
    case'S':
        joueur[tour%2]->ligne ++;
        break;
    case'E':
        joueur[tour%2]->colonne ++;
        break;
    case'W':
        joueur[tour%2]->colonne --;
        break;
    }
}

void positionner_pion(Joueur* joueur[2], Plateau* plateau,int tour)
{
    plateau->grille[joueur[tour%2]->ligne][joueur[tour%2]->colonne] = joueur[tour%2]->pion;
}

void attribution_point(Joueur* joueur[2],int tour)
{
    if (tour%2 == 1)
    {
        joueur[0]->victoires ++;
    }
    else
    {
        joueur[1]->victoires ++;
    }
}

void affichage_point(Joueur* joueur[2])
{
    gotoxy(73, 11);
    printf("Scores");
    gotoxy(70, 12);
    printf("Joueur 1: %d\n", joueur[0]->victoires);
    gotoxy(70, 13);
    printf("Joueur 2: %d\n", joueur[1]->victoires);
}

void detruire_plateau(Plateau** adr_plateau)
{
    Plateau* plateau = *adr_plateau;
    for(int i = 0; i < plateau->lignes; i++)
    {
        free(plateau->grille[i]);
    }
    free(plateau->lignes);
    free(plateau->colonnes);
    free(plateau);
    *adr_plateau = NULL;
}

void detruire_joueurs(Joueur** adr_joueur)
{
    Joueur* joueur = *adr_joueur;
    free(joueur->victoires);
    free(joueur->ligne);
    free(joueur->colonne);
    free(joueur->pion);
    free(joueur);
    *adr_joueur = NULL;
}*/
