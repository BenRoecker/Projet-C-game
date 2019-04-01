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

int somme_lignes(Plateau* plateau, int li, int c)//int ligne, int colonne
{
    char self = plateau -> grille[li][c]; //Le caractère que l'on cherche est celui à la position de départ
    int total = 1, cases = min(3,c); //Le nombre de cases à tester est le minimum entre 3 et le nombre de cases avant la bordure
    for(int i = 1; i <= cases; i++)
    {
        if(plateau -> grille[li][c-i] == self) //Somme à gauche
        {
            total++;
            if(total == 4) //Si on a trouvé un alignement de 4 on s'arrête (on ne différencie donc pas un alignement de 4, 5, 6, etc)
            {
                return 4;
            }
        }
        else //Si le pion adjascent n'est pas du même type que celui testé, on s'arrête
        {
            break;
        }
    }
    cases = min(3, plateau->colonnes - 1 - c); //Le nombre de cases à tester est le minimum entre 3 et le nombre de cases avant l'autre bordure
    for(int i = 1; i <= cases; i++)
    {
        if(plateau -> grille[li][c+i] == self) //Somme à droite
        {
            total++;
            if(total == 4) //Idem ; noter que total n'est pas remi à 0 pour compter un pion qui viendrait faire le lien entre deux bouts séparés
            {
                return 4;
            }
        }
        else //idem
        {
            break;
        }
    }
    return total; //Si on a moins de 4 pions alignés, on renvoie tout de même combien on en a pour pouvoir afficher le maximum
}

int somme_colonnes(Plateau* plateau, int li, int c)//int ligne, int colonne
{
    char self = plateau -> grille[li][c]; //Le caractère que l'on cherche est celui à la position de départ
    int total = 1, cases = min(3, plateau->lignes - 1 - li); //Le nombre de cases à tester est le minimum entre 3 et le nombre de cases avant la bordure
    for(int i = 1; i <= cases; i++)
    {
        if(plateau -> grille[li+i][c] == self) //Somme en dessous
        {
            total++;
            if(total == 4) //Si on a trouvé un alignement de 4 on s'arrête (on ne différencie donc pas un alignement de 4, 5, 6, etc)
            {
                return 4;
            }
        }
        else //Si le pion adjascent n'est pas du même type que celui testé, on s'arrête
        {
            break;
        }
    }
    //Cette fois on ne teste pas l'autre côté (qui serait au dessus du pion) car il est impossible qu'il y ait déjà des pions au dessus
    return total; //Si on a moins de 4 pions alignés, on renvoie tout de même combien on en a pour pouvoir afficher le maximum
}

int somme_diag_descendante(Plateau* plateau, int li, int c)//int ligne, int colonne
{
    //Si on se trouve dans le coin inférieur gauche ou le coin suppérieur droit, alors pas la peine de tester car on n'a pas la place de former une diagonale
    if((li > 3 && c < 4 && (li - c) > 2) || (li < 4 && c > 4 && (c - li) > 3))
    {
        return 0;
    }
    char self = plateau -> grille[li][c];
    int total = 1, cases = min(3,min(li,c));
    for(int i = 1; i <= cases; i++)
    {
        if(plateau -> grille[li-i][c-i] == self) //Moitié de diagonale vers le NO
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
        if(plateau -> grille[li+i][c+i] == self) //Moitié de diagonale vers le SE
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
    //Si on se trouve dans le coin inférieur droit ou le coin suppérieur gauche, alors pas la peine de tester car on n'a pas la place de former une diagonale
    if((li > 3 && c > 4 && (li + c) < 5 ) || (li < 4 && c < 4 && (li + c) > 10))
    {
        return 0;
    }
    char self = plateau -> grille[li][c];
    int total = 1, cases = min(3,min(plateau->lignes - 1 - li,c));
    for(int i = 1; i <= cases; i++)
    {
        if(plateau -> grille[li+i][c-i] == self) //Moitié de diagonale vers le SO
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
        if(plateau -> grille[li-i][c+i] == self) //Moitié de diagonale vers le NE
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
    //On regarde la somme des pions alignés dans chaque direction
    int s_lignes = somme_lignes(plateau, li, c);
    if(s_lignes == 4) //Test successifs pour eviter de continuer à compter si on a déjà une combinaison gagnante
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
    return max(s_lignes,max(s_colonnes,max(s_diag_bas,s_diag_haut))); //Si aucun ne vaut 4, on renvoie tout de même le maximum pour pouvoir l'afficher
}

int is_draw(Plateau* plateau)
{
    for(int i = 0; i < plateau->colonnes; i++)
    {
        if(plateau->grille[0][i] == '.') //S'il reste au moins une colonne non pleine, la partie peut continuer. Noter qu'on ne regarde que la case la plus haut car c'est celle qui se remplit en dernier
        {
            return 0;
        }
    }
    return 1; //Si on a trouvé aucune case vide, alors c'est match nul
}

int obtenir_entree(Plateau* plateau)
{
    printf("\n\n\nDans quelle colonne jouer ?\n");
    int asw;
    scanf("%d",&asw);
    while(asw < 1 || asw > (plateau -> colonnes)) //Si l'utilisateur rentre une valeur en dehors des limites
    {
        //On redemande jusqu'à ce qu'il donne une valeur correcte
        printf("Veuillez entrer un nombre compris entre 1 et %d (inclus)\n",plateau -> colonnes);
        scanf(" %d",&asw);
        //Noter qu'on ne vérifie pas ici si la colonne est vide ou non
    }
    return asw-1; //On a demandé à l'utilisateur une valeur entre 1 et X car plus intuitif pour un humain, mais on converti derrière pour l'ordinateur
}

void jouer(Plateau* plateau, char symbole, int coords[2])
{
    int asw = obtenir_entree(plateau);
    while((plateau->grille[0][asw]) != '.') //Si l'utilisateur à demandé une colonne pleine, on lui demande de choisir autre part
    {
        printf("\nVeuillez entrer une colonne non complete\n");
        asw = obtenir_entree(plateau);
    }
    int li;
    //En partant de la case la plus basse (dernier élément de la liste) on remonte jusqu'à trouver la première case vide que l'on remplit
    for(int i = plateau->lignes-1; i >= 0; i--)
    {
        if((plateau->grille[i][asw]) == '.')
        {
            plateau->grille[i][asw] = symbole; //Bien qu'on affiche un petit carré, dans la mémoire on stocke autre chose pour différencier les pions placés par un joueur ou l'autre
            li = i;
            break;
        }
    }
    //On renvoie les coordonnées auxquelles on a joué pour pouvoir vérifier autre part si c'est une victoire
    coords[0] = li;
    coords[1] = asw;
}

void afficher_plateau(Plateau* plateau)
{
    //Affichage des numéros de colonnes
    for(int i = 0; i < plateau->colonnes; i++)
    {
        gotoxy(i*2+18,5);
        printf("%d",i+1);
    }
    //Affichage du tableau
    for(int i = 0; i < plateau->lignes; i++)
    {
        for(int n = 0; n < plateau->colonnes; n++)
        {
            //Choix de la couleur en fonction du caractère
            //Noter qu'on affiche toujours un petit carré, cependant dans la mémoire les pions de chaque joueurs sont stockés différement pour pouvoir les différencier
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
    //Affichage du numéro de tour
    textcolor(WHITE);
    gotoxy(35,5);
    printf("Tour numero %d", tours);
    //Affichage du joueur dont c'est le tour
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
    //Affichage du plateau
    afficher_plateau(plateau);
    //Affichage des alignements les plus longues
    gotoxy(35,10);
    printf("Le plus long alignement de ");
    textcolor(LIGHTRED);
    printf("%c",(char)254);
    textcolor(WHITE);
    printf(" fait %d cases", meilleure_combi_save[0]);
    gotoxy(35,11);
    printf("Le plus long alignement de ");
    textcolor(YELLOW);
    printf("%c",(char)254);
    textcolor(WHITE);
    printf(" fait %d cases", meilleure_combi_save[1]);
}

void afficher_victoire(Plateau* plateau, Joueur joueurs[2], int vainqueur)
{
    clrscr();
    //On réaffiche le plateau pour les joueurs, mais l'affichage général avec tour, score, joueur qui doit jouer, etc
    afficher_plateau(plateau);
    //On affiche le résultat de la partie
    switch(vainqueur) // -1 = égalité, 0 = J1, 1 = J2
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
    //On affiche les nouveaux scores
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
