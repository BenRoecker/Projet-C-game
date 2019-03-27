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
void afficherListe(Liste *liste);

int main()
{
    Joueur joueurs[2];
    int i;
    for (i = 0; i < 2; i++)
    {
        printf("J%d choisi un charactere: \n", i+1);
        scanf(" %c", &(joueurs[i].pion));
        joueurs[i].victoires = 0;
    }
    printf("Hello world!\n");
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

    position->colonne = 21;
    position->ligne = lignes;
    position->suivant = NULL;
    liste->premier = position;

    return liste;
}
void afficherListe(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Position *actuel = liste->premier;

    while (actuel != NULL)
    {
        printf("%d -> ", actuel->colonne);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}
