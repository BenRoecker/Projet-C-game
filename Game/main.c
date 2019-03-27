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
    int victoires;
    char pion;
} Joueur;


typedef struct Position Position;
struct Position
{
    int colonne;
    int ligne;
    Position* suivant;
};

typedef struct Liste Liste;
struct Liste
{
    Position* premier;
};

Plateau* creer_plateau(int lignes, int colonnes);
Joueur* creer_joueur(char pions);
Liste* initialisation(int lignes);
void afficherListe(Liste *listej2, Plateau* plateau,Joueur joueur);
void afficher_plateau(Plateau* plateau);

int main()
{
    Joueur joueurs[2];
    int i;
    for (i = 0; i < 2; i++)
    {
        joueurs[i].pion = (char)219;
        joueurs[i].victoires = 0;
    }
    printf("Hello world!\n");
    Plateau* plateau = creer_plateau(21, 21);
    Liste* listej1 = initialisation(6);
    Liste* listej2 = initialisation(16);
    afficherListe(listej2, plateau, joueurs[0]);
    afficherListe(listej1, plateau, joueurs[1]);
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
    return joueur;
}
Liste* initialisation(int lignes)
{
    Liste* liste = malloc(sizeof(*liste));
    Position* position = malloc(sizeof(*position));

    if (liste == NULL || position == NULL)
    {
        exit(EXIT_FAILURE);
    }

    position->colonne = 12;
    position->ligne = lignes;
    position->suivant = NULL;
    liste->premier = position;

    return liste;
}
void afficherListe(Liste *liste, Plateau* plateau,Joueur joueur)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Position *actuel = liste->premier;

    while (actuel != NULL)
    {
        plateau->grille[actuel->ligne][actuel->colonne] = joueur.pion;
        printf("%d : %d ->", actuel->ligne, actuel->colonne);
        actuel = actuel->suivant;
    }
    printf("\n");
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
