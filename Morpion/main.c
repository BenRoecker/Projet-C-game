#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "conio.h"
#include "morpion_func.h"

void morpion();

int main()
{
    srand(time(NULL));
    morpion();
    return 0;
}

void morpion()
{
    //Création des données générales
    Plateau* plateau;
    char continuer = 'Y';
    int tours;
    Joueur joueurs[2];
    char pions[2] = {'X','O'};
    for(int i = 0; i<2; i++)
    {
        joueurs[i].victoires = 0;
        joueurs[i].pion = pions[i];
    }
    do
    {
        //Initialisation des données de la partie
        tours = 1;
        plateau = creer_plateau(3, 3);
        //Boucle de logique principale
        while(1)
        {
            display(plateau, joueurs, tours);
            play(plateau, 2-(tours%2), joueurs);
            if(is_winning(plateau, joueurs))
            {
                displayWin(plateau, joueurs, tours);
                break;
            }
            if(is_draw(plateau))
            {
                displayDraw(plateau, joueurs);
                break;
            }
            tours++;
        }
        do
        {
            printf("\n\nVoulez-vous rejouer ? [Y/N]\n");
            continuer = getch();
        }
        while(continuer != 'Y' && continuer != 'N');
        detruire_plateau(&plateau);
    }
    while(continuer == 'Y');
}
