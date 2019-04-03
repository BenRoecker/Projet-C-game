#include <stdio.h>
#include <stdlib.h>

#include "puissance4_func.h"

void puissance4();

int main()
{
    puissance4();
    return 0;
}

void puissance4()
{
    //Création des données générales
    Plateau* plateau;
    Joueur joueurs[2];
    const char pions[2] = {'X','A'};
    for(int i = 0; i<2; i++)
    {
        joueurs[i].victoires = 0;
        joueurs[i].pion = pions[i];
    }
    char continuer = 'Y';
    //Début de la partie
    while(continuer == 'Y')
    {
        //Intialisation des données de la partie
        plateau = creer_plateau(6,7);
        int tours = 0, vainqueur = -1, meilleure_combi = 0;
        int meilleure_combi_save[2] = {0,0};
        int coords[2];
        while(1)
        {
            tours++;
            affichage(plateau, tours, meilleure_combi_save);
            jouer(plateau, joueurs[1-tours%2].pion, coords);
            meilleure_combi = is_winning(plateau, coords[0], coords[1]); //On regarde quelle combinaison est la meilleure autour du nouveau pion
            meilleure_combi_save[1-tours%2] = max(meilleure_combi_save[1-tours%2], meilleure_combi); //On regarde si la nouvelle combinaison est mieux que l'ancienne meilleure
            if(meilleure_combi == 4) //Si le joueur a aligné 4 pion
            {
                vainqueur = 1-tours%2; //Alors il gagne
                break; //Et on s'arrête
            }
            else if(is_draw(plateau)) //S'il y a match nul, on s'arrête là
            {
                break;
            }
        }
        afficher_victoire(plateau, joueurs, vainqueur);
        do
        {
            printf("\nRefaire une partie ? (Y/N)\n");
            continuer = getch();
        }
        while(continuer != 'Y' && continuer != 'N');
        detruire_plateau(&plateau);
    }
}
