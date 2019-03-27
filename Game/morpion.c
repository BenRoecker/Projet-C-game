#include "morpion_func.h"
#include "morpion.h"

void morpion()
{
    Plateau* plateau;
    char continuer = 'Y';
    int i;
    Joueur joueurs[2];
    char pions[2] = {'X','O'};
    for(i=0; i<2; i++)
    {
        joueurs[i].victoires = 0;
        joueurs[i].pion = pions[i];
    }
    do
    {
        plateau = creer_plateau(3, 3);
        display(plateau, joueurs, 1);
        while(1)
        {
            play(plateau, 1, joueurs);
            display(plateau, joueurs, 2);
            if(is_winning(plateau, joueurs))
            {
                clrscr();
                displayGrid(plateau, joueurs);
                printf("\n\nLe joueur 1 gagne !\n");
                joueurs[0].victoires += 1;
                break;
            }
            if(is_draw(plateau))
            {
                clrscr();
                displayGrid(plateau, joueurs);
                printf("\n\nPersonne ne gagne !\n");
                break;
            }
            play(plateau, 2, joueurs);
            display(plateau, joueurs, 1);
            if(is_winning(plateau, joueurs))
            {
                clrscr();
                displayGrid(plateau, joueurs);
                printf("\n\nLe joueur 2 gagne !\n");
                joueurs[1].victoires += 1;
                break;
            }
        }
        printf("\nScores : \n\nJoueur 1 : %d \tJoueur 2 : %d\n",joueurs[0].victoires,joueurs[1].victoires);
        do
        {
            printf("\nVoulez-vous rejouer ? [Y/N]\n");
            scanf(" %c",&continuer);
        }
        while(continuer != 'Y' && continuer != 'N');
        detruire_plateau(&plateau);
    }
    while(continuer == 'Y');
}
