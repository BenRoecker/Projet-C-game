#include <stdio.h>
#include <stdlib.h>
#include "puissance4_func.h"
#include "conio.h"


int min(int a, int b)
{
    if(a<b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int max(int a, int b)
{
    if(a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
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

int somme_lignes(Plateau* plateau, int li, int c)//int ligne, int colonne
{
    char self = plateau -> grille[li][c];
    int total = 1, cases = min(3,c);
    for(int i = 1; i <= cases; i++)
    {
        if(plateau -> grille[li][c-i] == self)
        {
            total++;
            if(total == 4)
            {
                return 4;
            }
        }
        else
        {
            break;
        }
    }
    cases = min(3, plateau->colonnes - 1 - c);
    for(int i = 1; i <= cases; i++)
    {
        if(plateau -> grille[li][c+i] == self)
        {
            total++;
            if(total == 4)
            {
                return 4;
            }
        }
        else
        {
            break;
        }
    }
    return total;
}

int somme_colonnes(Plateau* plateau, int li, int c)//int ligne, int colonne
{
    char self = plateau -> grille[li][c];
    int total = 1, cases = min(3, plateau->lignes - 1 - li);
    for(int i = 1; i <= cases; i++)
    {
        if(plateau -> grille[li+i][c] == self)
        {
            total++;
            if(total == 4)
            {
                return 4;
            }
        }
        else
        {
            break;
        }
    }
    return total;
}

int somme_diag_descendante(Plateau* plateau, int li, int c)//int ligne, int colonne
{
    if((li > 3 && c < 4 && (li - c) > 2) || (li < 4 && c > 4 && (c - li) > 3)) //Les coordonnées dans lesquelles un pion ne complétera jamais une diagonale
    {
        return 0;
    }
    char self = plateau -> grille[li][c];
    int total = 1, cases = min(3,min(li,c));
    for(int i = 1; i <= cases; i++)
    {
        if(plateau -> grille[li-i][c-i] == self)
        {
            total++;
            if(total == 4)
            {
                return 4;
            }
        }
        else
        {
            break;
        }
    }
    cases = min(3,min(plateau->lignes - 1 - li, plateau->colonnes - 1 - c));
    for(int i = 1; i <= cases; i++)
    {
        if(plateau -> grille[li+i][c+i] == self)
        {
            total++;
            if(total == 4)
            {
                return 4;
            }
        }
        else
        {
            break;
        }
    }
    return total;
}

int somme_diag_montante(Plateau* plateau, int li, int c)//int ligne, int colonne
{
    if((li > 3 && c > 4 && (li + c) < 5 ) || (li < 4 && c < 4 && (li + c) > 10)) //Les coordonnées dans lesquelles un pion ne complétera jamais une diagonale
    {
        return 0;
    }
    char self = plateau -> grille[li][c];
    int total = 1, cases = min(3,min(plateau->lignes - 1 - li,c));
    for(int i = 1; i <= cases; i++)
    {
        if(plateau -> grille[li+i][c-i] == self)
        {
            total++;
            if(total == 4)
            {
                return 4;
            }
        }
        else
        {
            break;
        }
    }
    cases = min(3,min(li, plateau->colonnes - 1 - c));
    for(int i = 1; i <= cases; i++)
    {
        if(plateau -> grille[li-i][c+i] == self)
        {
            total++;
            if(total == 4)
            {
                return 4;
            }
        }
        else
        {
            break;
        }
    }
    return total;
}

int is_winning(Plateau* plateau, int li, int c) //int ligne, int colonne
{
    int s_lignes = somme_lignes(plateau, li, c);
    if(s_lignes == 4) //return successifs pour eviter de continuer à compter si on a déjà une combinaison gagnante
    {
        return 4;
    }
    int s_colonnes = somme_colonnes(plateau, li, c);
    if(s_colonnes == 4)
    {
        return 4;
    }
    int s_diag_bas = somme_diag_descendante(plateau, li, c);
    if(s_diag_bas == 4)
    {
        return 4;
    }
    int s_diag_haut = somme_diag_montante(plateau, li, c);
    if(s_diag_haut == 4)
    {
        return 4;
    }
    return max(s_lignes,max(s_colonnes,max(s_diag_bas,s_diag_haut)));
}

int is_draw(Plateau* plateau)
{
    for(int i = 0; i < plateau->colonnes; i++)
    {
        if(plateau->grille[0][i] == '.')
        {
            return 0;
        }
    }
    return 1;
}

int obtenir_entree(Plateau* plateau)
{
    printf("\n\n\nDans quelle colonne jouer ?\n");
    int asw;
    scanf("%d",&asw);
    while(asw < 1 || asw > (plateau -> colonnes))
    {
        printf("Veuillez entrer un nombre compris entre 1 et %d (inclus)\n",plateau -> colonnes);
        scanf(" %d",&asw);
    }
    return asw-1;
}

void jouer(Plateau* plateau, char symbole, int coords[2])
{
    int asw = obtenir_entree(plateau);
    while((plateau->grille[0][asw]) != '.')
    {
        printf("\nVeuillez entrer une colonne non complete\n");
        asw = obtenir_entree(plateau);
    }
    int li;
    for(int i = plateau->lignes-1; i >= 0; i--)
    {
        if((plateau->grille[i][asw]) == '.')
        {
            plateau->grille[i][asw] = symbole;
            li = i;
            break;
        }
    }
    coords[0] = li;
    coords[1] = asw;
    //printf("\nlignes : %d,    colonnes : %d,    diag bas : %d,     diag haut : %d\n",win_lignes(plateau,li,asw),win_colonnes(plateau,li,asw),win_diag_descendante(plateau,li,asw),win_diag_montante(plateau,li,asw));
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
        for(int n = 0; n < plateau->colonnes; n++)
        {
            gotoxy(n*2+18,i+6);
            switch(plateau -> grille[i][n])
            {
            case '.':
                printf(".");
                break;
            case 'A':
                textcolor(YELLOW);
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

void affichage(Plateau* plateau, int tours, int meilleure_combi_save[2])
{
    clrscr();
    textcolor(WHITE);
    gotoxy(35,5);
    printf("Tour numero %d", tours);
    gotoxy(35,6);
    printf("Au joueur ");
    if(tours%2 == 1)
    {
        textcolor(LIGHTRED);
    }
    else
    {
        textcolor(YELLOW);
    }
    printf("%c",(char)254);
    textcolor(WHITE);
    printf(" de jouer.");
    afficher_plateau(plateau);
    gotoxy(35,10);
    printf("La combinaison la plus longue de ");
    textcolor(LIGHTRED);
    printf("%c",(char)254);
    textcolor(WHITE);
    printf(" est de taille %d", meilleure_combi_save[0]);
    gotoxy(35,11);
    printf("La combinaison la plus longue de ");
    textcolor(YELLOW);
    printf("%c",(char)254);
    textcolor(WHITE);
    printf(" est de taille %d", meilleure_combi_save[1]);
}

void afficher_victoire(Plateau* plateau, Joueur joueurs[2], int vainqueur)
{
    clrscr();
    afficher_plateau(plateau);
    switch(vainqueur)
    {
    case -1:
        printf("\n\nEgalite, personne ne gagne.\n");
        break;
    case 0: //le joueur 1 gagne
        joueurs[0].victoires++;
        printf("\n\nLe vainqueur est le joueur ");
        textcolor(LIGHTRED);
        printf("%c",(char)254);
        textcolor(WHITE);
        break;
    case 1: //le joueur 2 gagne
        joueurs[1].victoires++;
        printf("\n\nLe vainqueur est le joueur ");
        textcolor(YELLOW);
        printf("%c",(char)254);
        textcolor(WHITE);
        break;
    }
    printf("\n\nScores :\n");
    textcolor(LIGHTRED);
    printf("%c",(char)254);
    textcolor(WHITE);
    printf(" : %d\n",joueurs[0].victoires);
    textcolor(YELLOW);
    printf("%c",(char)254);
    textcolor(WHITE);
    printf(" : %d\n",joueurs[1].victoires);
}
