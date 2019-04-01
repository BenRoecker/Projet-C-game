#include <stdlib.h>

#include "common_func.h"

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

void detruire_plateau(Plateau** adr_plateau)
{
    Plateau* plateau = *adr_plateau;
    for(int i = 0; i < plateau->lignes; i++)
    {
        free(plateau->grille[i]);
    }
    free(plateau);
    *adr_plateau = NULL;
}
