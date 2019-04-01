#include <stdio.h>
#include <stdlib.h>

#include "tron_func.h"

void tron();

int main()
{
    tron();
    return 0;
}

void tron()
{
    char rejouer, show_replay;
    int tour = 0;
    Joueur* joueurs[2];
    joueurs[0] = creer_joueur('A');
    joueurs[1] = creer_joueur('X');
    Plateau* plateau = creer_plateau(21, 21);
    chained_list* replay;
    do
    {
        tour = 0;
        replay = create_chained();
        show_replay = 'N';
        initialiser_plateau(plateau);
        pos_initial(joueurs[0], 6, plateau);
        initialize_chained(replay, joueurs[0]->ligne, joueurs[0]->colonne, joueurs[0]->pion);
        pos_initial(joueurs[1], 14, plateau);
        append_chained(replay, joueurs[1]->ligne, joueurs[1]->colonne, joueurs[1]->pion);
        do
        {
            affichage(joueurs, plateau, tour);
            obtenir_entree(joueurs, tour);
            append_chained(replay, joueurs[tour%2]->ligne, joueurs[tour%2]->colonne, joueurs[tour%2]->pion);
            if (!defaite(joueurs, plateau, tour))
            {
                positionner_pion(joueurs, plateau, tour);
            }
            else
            {
                affichage_defaite(joueurs, plateau, tour);
                break;
            }
            tour ++;
        }while(1);
        attribution_point(joueurs, tour);
        do
        {
            printf("Voulez vous voir le replay ? (Y/N)\n");
            scanf(" %c", &show_replay);
        }while (show_replay != 'Y' && show_replay != 'N');
        if(show_replay == 'Y')
        {
            rejouer_partie(replay);
        }
        destroy_chained(replay);
        do
        {
            printf("\nVoulez vous rejouer ? (Y/N)\n");
            scanf(" %c", &rejouer);
        }while (rejouer != 'Y' && rejouer != 'N');
        clrscr();
        destroy_chained(replay);
    }while (rejouer == 'Y');
    detruire_plateau(&plateau);
    detruire_joueurs(&joueurs[0]);
    detruire_joueurs(&joueurs[1]);
}
