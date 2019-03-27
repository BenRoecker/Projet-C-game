#include <stdio.h>
#include <stdlib.h>
#include "puissance4.h"
#include "puissance4_func.h"
#include "conio.h"


void puissance4()
{
    Plateau* plateau;
    Joueur joueurs[2];
    const char pions[2] = {'X','A'};
    for(int i = 0; i<2; i++)
    {
        joueurs[i].victoires = 0;
        joueurs[i].pion = pions[i];
    }
    char continuer = 'Y';
    while(continuer == 'Y')
    {
        plateau = creer_plateau(6,7);
        int tours = 0, vainqueur = -1, meilleure_combi = 0;
        int meilleure_combi_save[2] = {0,0};
        int coords[2];
        while(1)
        {
            tours++;
            affichage(plateau, tours, meilleure_combi_save);
            jouer(plateau, joueurs[1-tours%2].pion, coords);
            meilleure_combi = is_winning(plateau, coords[0], coords[1]);
            meilleure_combi_save[1-tours%2] = max(meilleure_combi_save[1-tours%2], meilleure_combi);
            if(meilleure_combi == 4)
            {
                vainqueur = 1-tours%2;
                break;
            }
            else if(is_draw(plateau))
            {
                break;
            }
        }
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
            textcolor(LIGHTRED);
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

        do
        {
            printf("\nRefaire une partie ? (Y/N)\n");
            scanf(" %c",&continuer);
        }
        while(continuer != 'Y' && continuer != 'N');

        detruire_plateau(&plateau);
    }
}
