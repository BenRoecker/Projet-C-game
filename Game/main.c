#include <stdio.h>
#include <stdlib.h>
#include "conio.h"

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
int deplacement(Joueur* joueur, Plateau* plateau, int numerojoueur);
int defaite(Joueur* joueur, Plateau* plateau);
void initialiser_plateau(Plateau* plateau);

int main()
{
    char rejouer;
    Joueur joueurs[2];
    int i;
    for (i = 0; i < 2; i++)
    {
        joueurs[i].victoires = 0;
    }
    joueurs[0].pion = 'A';
    joueurs[1].pion = 'X';
    Plateau* plateau = creer_plateau(21, 21);
    do
    {
        int victoire;
        int tour = 1;
        initialiser_plateau(plateau);
        pos_initial(&joueurs[0], 6, plateau);
        pos_initial(&joueurs[1], 16, plateau);
        do
        {
            afficher_plateau(plateau);
            gotoxy(1,27);
            printf("Tour %d", tour);
            gotoxy(1,28);
            textcolor(LIGHTCYAN);
            printf("c'est au joueur 1 de jouer");
            textcolor(WHITE);
            victoire = deplacement(&joueurs[0], plateau, 1);
            if (victoire == 1)
            {
                break;
            }
            afficher_plateau(plateau);
            gotoxy(1,28);
            textcolor(LIGHTRED);
            printf("c'est au joueur 2 de jouer");
            textcolor(WHITE);
            victoire = deplacement(&joueurs[1], plateau, 2);
            afficher_plateau(plateau);
            tour ++;
        }while(victoire == 0);
        afficher_plateau(plateau);
        do
        {
            printf("voulez vous rejouer ? (Y/N)");
            scanf(" %c", &rejouer);
        }while (rejouer != 'Y' && rejouer != 'N');
    }while (rejouer == 'Y');
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
    joueur->ligne = 0;
    return joueur;
}

void afficher_plateau(Plateau* plateau)
{
    for(int i = 0; i < plateau->colonnes; i++)
    {
        gotoxy(i*2+18,5);
        printf("%d",i+1);
    }
    for(int i = 0; i < plateau->lignes; i++)
    {
        gotoxy(16,i+6);
        printf("%d",i+1);
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

int deplacement(Joueur* joueur, Plateau* plateau,int numerojoueur)
{
    int non_victoire = 0;
    char direction;
    do
    {
        gotoxy(1,29);
        printf("Quelle est la direction (N/S/E/W):");
        scanf(" %c", &direction);
    }while (direction != 'N' && direction != 'S' && direction != 'E' && direction != 'W');
    clrscr();
    switch(direction)
    {
    case'N':
        if (joueur->ligne == 0)
        {
            non_victoire = 1;
        }
        else
        {
            joueur->ligne = joueur->ligne -1;
        }
        break;
    case'S':
        if (joueur->ligne == 20)
        {
            non_victoire = 1;
        }
        else
        {
            joueur->ligne = joueur->ligne +1;
        }
        break;
    case'E':
        if (joueur->colonne == 20)
        {
            non_victoire = 1;
        }
        else
        {
            joueur->colonne = joueur->colonne + 1;
        }
        break;
    case'W':
        if (joueur->colonne == 0)
        {
            non_victoire = 1;
        }
        else
        {
            joueur->colonne = joueur->colonne - 1;
        }
        break;
    }
    if(non_victoire == 1 || defaite(joueur, plateau))
    {
        gotoxy(1,31);
        printf("Joueur %d a perdu.", numerojoueur);
        return 1;
    }
    else
    {
        plateau->grille[joueur->ligne][joueur->colonne] = joueur->pion;
        return 0;
    }
}



int defaite(Joueur* joueur, Plateau* plateau)
{
    if(plateau->grille[joueur->ligne][joueur->colonne] != '.')
    {
        return 1;
    }
    else
    {
        return 0;
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
