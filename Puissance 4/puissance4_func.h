#ifndef PUISSANCE4_FUNC_H_INCLUDED
#define PUISSANCE4_FUNC_H_INCLUDED

#include "common_func.h"

int min(int a, int b);
int max(int a, int b);
int somme_lignes(Plateau* plateau, int li, int c);
int somme_colonnes(Plateau* plateau, int li, int c);
int somme_diag_descendante(Plateau* plateau, int li, int c);
int somme_diag_montante(Plateau* plateau, int li, int c);
int is_winning(Plateau* plateau, int li, int c);
int is_draw(Plateau* plateau);
int obtenir_entree(Plateau* plateau);
void jouer(Plateau* plateau, char symbole, int coords[2]);
void afficher_plateau(Plateau* plateau);
void affichage(Plateau* plateau, int tours, int meilleure_combi_save[2]);
void afficher_victoire(Plateau* plateau, Joueur joueurs[2], int vainqueur);

#endif // PUISSANCE4_FUNC_H_INCLUDED
