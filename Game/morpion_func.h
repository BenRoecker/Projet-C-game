#ifndef MORPION_FUNC_H_INCLUDED
#define MORPION_FUNC_H_INCLUDED

typedef struct
{
    int victoires;
    char pion;
} Joueur;

typedef struct
{
    int lignes;
    int colonnes;
    char** grille;
} Plateau ;

Plateau* creer_plateau(int lignes, int colonnes);
void detruire_plateau(Plateau** adr_plateau);
void displayGrid(Plateau* plateau, Joueur joueurs[2]);
void display(Plateau* plateau, Joueur joueurs[2], int tours);
void displayWin(Plateau* plateau, Joueur joueurs[2], int tours);
void displayDraw(Plateau* plateau, Joueur joueurs[2]);
void getInput(int tab[2], int GRID_SIZE);
void play(Plateau* plateau, int player_num, Joueur joueurs[2]);
int is_winning(Plateau* plateau, Joueur joueurs[2]);
int is_draw(Plateau* plateau);

#endif // MORPION_FUNC_H_INCLUDED
