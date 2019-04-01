#include <windows.h>

#include "morpion_func.h"
#include "conio.h"

void displayGrid(Plateau* plateau, Joueur joueurs[2])
{
    int i,n;
    char temp;
    const int GRID_SIZE = plateau -> lignes; //plateau carré donc pas besoin de différentier les colonnes et les lignes
    //Affichage des numéros de lignes/colonnes
    textcolor(YELLOW);
    for (i=0; i < GRID_SIZE; i++)
    {
        gotoxy(i*2+18,4);
        printf("%d",i+1);
        gotoxy(16,i+5);
        printf("%d",i+1);
    }
    //Affichage de la grille
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
    //Affichage du numéro de tour
    gotoxy(17,2);
    printf("Tour %d", tours);
    //Affichage de la grille
    displayGrid(plateau, joueurs);
    //Affichage des scores et du joueur dont c'est le tour
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
    //Affichage du plateau sans le reste de l'interface
    displayGrid(plateau, joueurs);
    //Affichage du vainqueur & mise à jour des scores
    gotoxy(11,9);
    printf("Le joueur %d gagne !",2-(tours%2));
    joueurs[1-(tours%2)].victoires += 1;
    //Affichage des scores
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
    //Affichage du plateau sans le reste de l'interface
    displayGrid(plateau, joueurs);
    //Affichage du message d'égalité & des scores
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
    while(tab[1] < 1 || tab[1] > GRID_SIZE) //On vérifie que le nombre indiqué soit bien dans les limites du plateau
    {
        printf("\nVeuillez entrer un nombre entre 1 et %d\n",GRID_SIZE);
        scanf("%d",&tab[1]);
    }
    printf("\nDans quelle ligne jouer ? [1,%d]\n",GRID_SIZE);
    scanf("%d",&tab[0]);
    while(tab[0] < 1 || tab[0] > GRID_SIZE) //Idem
    {
        printf("\nVeuillez entrer un nombre entre 1 et %d\n",GRID_SIZE);
        scanf("%d",&tab[0]);
    }
    //Noter qu'on ne vérifie pas ici si la case est vide
    //Retour multiple
    tab[0] -= 1; //On a demandé à l'utilisateur une valeur entre 1 et X car plus intuitif
    tab[1] -= 1; //Donc on converti pour l'ordinateur
}

void play(Plateau* plateau, int player_num, Joueur joueurs[2])
{
    int coords[2];
    //Si c'est au tour de l'humain
    if(player_num == 1)
    {
        getInput(coords, plateau -> lignes); //On récupère son entrée
        while(plateau -> grille[coords[0]][coords[1]] != '.') //S'il donne une case déjà occupée, on lui en demande une autre jusqu'à ce que ce soit correct
        {
            printf("\nVeuillez entrer des coordonnees valides\n");
            getInput(coords, plateau -> lignes);
        }
        plateau -> grille[coords[0]][coords[1]] = joueurs[0].pion;
    }
    else //Si c'est au tour de l'ordinateur
    {
        do {
            coords[0] = rand()%3;
            coords[1] = rand()%3;
        }while(plateau -> grille[coords[0]][coords[1]] != '.'); //On génère des coordonnées aléatoires tant qu'on n'a pas une case vide
        plateau -> grille[coords[0]][coords[1]] = joueurs[1].pion;
        Sleep(2000); //On simule un temps de réflexion
    }
}

int is_winning(Plateau* plateau, Joueur joueurs[2])
{
    int i,n,somme;
    const int GRID_SIZE = plateau -> lignes;
    for(i=0; i<GRID_SIZE; i++)//Pour chaque ligne
    {
        somme = 0;
        for(n=0; n<GRID_SIZE; n++) //On fait la somme des numéro ASCII des caractères
        {
            somme += plateau -> grille[i][n];
        }
        if(somme == GRID_SIZE*joueurs[0].pion || somme == GRID_SIZE*joueurs[1].pion) //Si cette somme est le triple du numéro d'un des pions, alors c'est qu'on a un alignement et donc une victoire
        {
            return 1;
        }
    }
    for(i=0; i<GRID_SIZE; i++)//idem pour les colonnes
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
    for(i=0; i<GRID_SIZE; i++)//idem pour la diagonale descendante
    {
        somme += plateau -> grille[i][i];
    }
    if(somme == GRID_SIZE*joueurs[0].pion || somme == GRID_SIZE*joueurs[1].pion)
    {
        return 1;
    }
    somme = 0;
    for(i=0; i<GRID_SIZE; i++)//idem pour la diagonale montante
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
    //S'il reste au moins une case vide, alors on n'a pas égalité.
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
    //Si on a trouvé aucune case vide, alors on est bien dans le cas de l'égalité
    return 1;
}
