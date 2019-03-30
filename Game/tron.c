#include "tron_func.h"
#include "tron.h"
#include "conio.h"

void tron()
{
    char rejouer;
    int tour = 0;
    Joueur* joueurs[2];
    joueurs[0] = creer_joueur('A');
    joueurs[1] = creer_joueur('X');
    Plateau* plateau = creer_plateau(21, 21);
    do
    {
        tour = 0;
        initialiser_plateau(plateau);
        pos_initial(joueurs[0], 6, plateau);
        pos_initial(joueurs[1], 14, plateau);
        do
        {
            affichage(joueurs, plateau, tour);
            obtenir_entree(joueurs, tour);
            if (!defaite(joueurs, plateau, tour))
            {
                positionner_pion(joueurs, plateau, tour);
            }
            else
            {
                affichage_defaite(joueurs, tour);
                break;
            }
            tour ++;
        }while(1);
        attribution_point(joueurs, tour);
        do
        {
            printf("voulez vous rejouer ? (Y/N)");
            scanf(" %c", &rejouer);
        }while (rejouer != 'Y' && rejouer != 'N');
    }while (rejouer == 'Y');
    detruire_plateau(&plateau);
    detruire_joueurs(&joueurs[0]);
    detruire_joueurs(&joueurs[1]);
}
