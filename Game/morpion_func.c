#include <windows.h>

#include "morpion_func.h"
#include "conio.h"

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

void displayGrid(Plateau* plateau, Joueur joueurs[2])
{
    int i,n;
    char temp;
    const int GRID_SIZE = plateau -> lignes; //plateau carré donc pas besoin de différentier les colonnes et les lignes
    textcolor(YELLOW);
    for (i=0; i < GRID_SIZE; i++)
    {
        gotoxy(i*2+18,4);
        printf("%d",i+1);
        gotoxy(16,i+5);
        printf("%d",i+1);
    }
    for(i=0; i<GRID_SIZE; i++)
    {
        for(n=0; n<GRID_SIZE; n++)
        {
            temp = plateau -> grille[i][n];
            if(temp == joueurs[0].pion)
            {
                textcolor(LIGHTGREEN);
            }
            else if(temp == joueurs[1].pion)
            {
                textcolor(LIGHTRED);
            }
            else
            {
                textcolor(WHITE);
            }
            gotoxy(n*2+18,i+5);
            printf("%c",temp);
        }
    }
    textcolor(WHITE);
}

void display(Plateau* plateau, Joueur joueurs[2], int tours)
{
    int player_num = 2-(tours%2);
    clrscr();
    gotoxy(17,2);
    printf("Tour %d", tours);
    displayGrid(plateau, joueurs);
    gotoxy(16,9);
    printf("Scores :");
    gotoxy(4,11);
    if(player_num == 1)
    {
        textbackground(GREEN);
        printf("Joueur 1 : %d", joueurs[0].victoires);
        textbackground(BLACK);
        gotoxy(24,11);
        printf("Ordinateur : %d", joueurs[1].victoires);
    }
    else
    {
        printf("Joueur 1 : %d", joueurs[0].victoires);
        textbackground(LIGHTRED);
        gotoxy(24,11);
        printf("Joueur 2 : %d", joueurs[1].victoires);
        textbackground(BLACK);
    }
}

void displayWin(Plateau* plateau, Joueur joueurs[2], int tours)
{
    clrscr();
    displayGrid(plateau, joueurs);
    gotoxy(11,9);
    printf("Le joueur %d gagne !",2-(tours%2));
    joueurs[1-(tours%2)].victoires += 1;
    gotoxy(16,11);
    printf("Scores :");
    gotoxy(4,13);
    printf("Joueur 1 : %d", joueurs[0].victoires);
    gotoxy(24,13);
    printf("Ordinateur : %d", joueurs[1].victoires);
}
void displayDraw(Plateau* plateau, Joueur joueurs[2])
{
    clrscr();
    displayGrid(plateau, joueurs);
    gotoxy(11,9);
    printf("Personne ne gagne !");
    gotoxy(16,11);
    printf("Scores :");
    gotoxy(4,13);
    printf("Joueur 1 : %d", joueurs[0].victoires);
    gotoxy(24,13);
    printf("Ordinateur : %d", joueurs[1].victoires);
}

void getInput(int tab[2], int GRID_SIZE)
{
    printf("\n\nDans quelle colonne jouer ? [1,%d]\n",GRID_SIZE);
    scanf("%d",&tab[1]);
    while(tab[1] < 1 || tab[1] > GRID_SIZE)
    {
        printf("\nVeuillez entrer un nombre entre 1 et %d\n",GRID_SIZE);
        scanf("%d",&tab[1]);
    }
    printf("\nDans quelle ligne jouer ? [1,%d]\n",GRID_SIZE);
    scanf("%d",&tab[0]);
    while(tab[0] < 1 || tab[0] > GRID_SIZE)
    {
        printf("\nVeuillez entrer un nombre entre 1 et %d\n",GRID_SIZE);
        scanf("%d",&tab[0]);
    }
    tab[0] -= 1;
    tab[1] -= 1;
}

void play(Plateau* plateau, int player_num, Joueur joueurs[2])
{
    int coords[2];
    if(player_num == 1)
    {
        getInput(coords, plateau -> lignes);
        while(plateau -> grille[coords[0]][coords[1]] != '.')
        {
            printf("\nVeuillez entrer des coordonnees valides\n");
            getInput(coords, plateau -> lignes);
        }
        plateau -> grille[coords[0]][coords[1]] = joueurs[0].pion;
    }
    else
    {
        do {
            coords[0] = rand()%3;
            coords[1] = rand()%3;
        }while(plateau -> grille[coords[0]][coords[1]] != '.');
        plateau -> grille[coords[0]][coords[1]] = joueurs[1].pion;
        Sleep(2000);
    }
}

int is_winning(Plateau* plateau, Joueur joueurs[2])
{
    int i,n,somme;
    const int GRID_SIZE = plateau -> lignes;
    for(i=0; i<GRID_SIZE; i++)
    {
        somme = 0;
        for(n=0; n<GRID_SIZE; n++)
        {
            somme += plateau -> grille[i][n];
        }
        if(somme == GRID_SIZE*joueurs[0].pion || somme == GRID_SIZE*joueurs[1].pion)
        {
            return 1;
        }
    }
    for(i=0; i<GRID_SIZE; i++)
    {
        somme = 0;
        for(n=0; n<GRID_SIZE; n++)
        {
            somme += plateau -> grille[n][i];
        }
        if(somme == GRID_SIZE*joueurs[0].pion || somme == GRID_SIZE*joueurs[1].pion)
        {
            return 1;
        }
    }
    somme = 0;
    for(i=0; i<GRID_SIZE; i++)
    {
        somme += plateau -> grille[i][i];
    }
    if(somme == GRID_SIZE*joueurs[0].pion || somme == GRID_SIZE*joueurs[1].pion)
    {
        return 1;
    }
    somme = 0;
    for(i=0; i<GRID_SIZE; i++)
    {
        somme += plateau -> grille[GRID_SIZE-i-1][i];
    }
    if(somme == GRID_SIZE*joueurs[0].pion || somme == GRID_SIZE*joueurs[1].pion)
    {
        return 1;
    }

    return 0;
}

int is_draw(Plateau* plateau)
{
    int i,n;
    const int GRID_SIZE = plateau -> lignes;
    for(i=0; i < GRID_SIZE; i++)
    {
        for(n=0; n < GRID_SIZE; n++)
        {
            if(plateau -> grille[i][n] == '.')
            {
                return 0;
            }
        }
    }
    return 1;
}
