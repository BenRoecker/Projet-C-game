#ifndef COMMUN_FUNC_H_INCLUDED
#define COMMUN_FUNC_H_INCLUDED

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
void detruire_plateau(Plateau** adr_plateau);

#endif // COMMUN_FUNC_H_INCLUDED
