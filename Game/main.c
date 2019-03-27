#include <stdio.h>
#include <stdlib.h>

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
void deplacement(Joueur* joueur, Plateau* plateau);

int main()
{
    Joueur joueurs[2];
    int i;
    for (i = 0; i < 2; i++)
    {
        joueurs[i].victoires = 0;
    }
    joueurs[0].pion = 'X';
    joueurs[1].pion = 'A';
    printf("Hello world!\n");
    Plateau* plateau = creer_plateau(21, 21);
    afficher_plateau(plateau);
    pos_initial(&joueurs[0], 6, plateau);
    pos_initial(&joueurs[0], 16, plateau);
    afficher_plateau(plateau);
    deplacement(&joueurs[0], plateau);
    afficher_plateau(plateau);
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
        printf("%d",i+1);
    }
    printf("\n");
    for(int i = 0; i < plateau->lignes; i++)
    {
        printf("%d",i+1);
        for(int n = 0; n < plateau->colonnes; n++)
        {
            switch(plateau -> grille[i][n])
            {
            case '.':
                printf(".");
                break;
            case 'A':
                printf("%c", (char)196);
                break;
            case 'X':
                printf("%c", (char)196);
                break;
            }
        }
        printf("\n");
    }
}

void pos_initial(Joueur* joueur, int nombre, Plateau* plateau)
{
    plateau->grille[20][nombre] = joueur->pion;
    joueur->colonne = nombre;
    joueur->ligne = 20;

}

void deplacement(Joueur* joueur, Plateau* plateau)
{
    char direction;
    printf("Quelle est la direction (N/S/E/W):\n");
    scanf(" %c", &direction);
    switch(direction)
    {
    case'N':
        joueur->ligne = joueur->ligne -1;
        break;
    case'S':
        joueur->ligne = joueur->ligne +1;
        break;
    case'E':
        joueur->colonne = joueur->colonne + 1;
        break;
    case'W':
        joueur->colonne = joueur->colonne - 1;
        break;
    }
    plateau->grille[joueur->ligne][joueur->colonne] = joueur->pion;
}



