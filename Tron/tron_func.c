#include <windows.h>

#include "tron_func.h"

Joueur* creer_joueur(char pions)
{
    Joueur* joueur = malloc(sizeof(Joueur));
    joueur->victoires = 0;
    joueur->pion = pions;
    return joueur;
}

void afficher_plateau(Plateau* plateau, Joueur* joueur[2])
{
    for(int i = 0; i < plateau->lignes; i++)
    {
        for(int n = 0; n < plateau->colonnes; n++)
        {
            gotoxy(n*2+18,i+6);
            switch(plateau -> grille[i][n])
            {
            case '.':
                textcolor(WHITE);
                printf(".");
                break;
            case 'A':
                textcolor(LIGHTCYAN);
                if(joueur[0]->ligne == i && joueur[0]->colonne == n)//condition pour afficher la tete de serpent
                {
                    printf("%c", (char)219);
                }
                else//sinon on affiche le caractère du corps
                {
                    printf("%c", (char)254);
                }
                break;
            case 'X':
                textcolor(LIGHTRED);
                if(joueur[1]->ligne == i && joueur[1]->colonne == n)//condition pour afficher la tete de serpent
                {
                    printf("%c", (char)219);
                }
                else
                {
                    printf("%c", (char)254);
                }
                break;
            }
            textcolor(WHITE);
        }
    }
}

void pos_initial(Joueur* joueur, int nombre, Plateau* plateau)
{
    plateau->grille[10][nombre] = joueur->pion;
    joueur->colonne = nombre;
    joueur->ligne = 10;

}

int defaite(Joueur* joueur[2], Plateau* plateau,int tour)
{
    if (joueur[tour%2]->ligne == -1 ||
        joueur[tour%2]->ligne == 21 ||
        joueur[tour%2]->colonne == -1 ||
        joueur[tour%2]->colonne == 21)//Condition de sortie du plateau
    {
        return 1;
    }
    else
    {
        if(plateau->grille[joueur[tour%2]->ligne][joueur[tour%2]->colonne] != '.')//condition entree dans soi-meme ou autre joueurs
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

 void initialiser_plateau(Plateau* plateau)
 {
     int i,j;
     for (i = 0; i < plateau->colonnes; i++)
     {
         for (j = 0; j < plateau->lignes; j++)
         {
             plateau->grille[i][j] = '.';
         }
     }
 }

void affichage(Joueur* joueur[2], Plateau* plateau, int tour)
{
    textcolor(YELLOW);
    gotoxy(29, 3);
    printf("Les Pietons de tron");
    afficher_plateau(plateau, joueur);
    affichage_point(joueur);
    gotoxy(1,27);
    printf("Tour %d", tour+1);
    gotoxy(1,28);
    if (tour%2 == 0)
    {
        textcolor(LIGHTCYAN);
    }
    else
    {
        textcolor(LIGHTRED);
    }
    printf("C'est au joueur %d de jouer.", tour%2+1);
    textcolor(WHITE);
}

void affichage_defaite(Joueur* joueur[2], Plateau* plateau, int tour)
{
    joueur[tour%2] -> ligne = -1;
    joueur[tour%2] -> colonne = -1;
    affichage(joueur, plateau, tour);
    gotoxy(1,30);
    printf("Joueur %d a perdu.\n", tour%2+1);
}

void obtenir_entree(Joueur* joueur[2],int tour)//Choix des coordonnee americaine
{
    char direction;
    gotoxy(1,29);
    do
    {
        printf("Ou veux-tu aller ?(N/S/E/W)\n");
        direction = getch();
        printf("\n");
    }while (direction != 'N' && direction != 'S' && direction != 'E' && direction != 'W');//blindage des entrees
    clrscr();
    switch(direction)
    {
    case'N':
        joueur[tour%2]->ligne --;
        break;
    case'S':
        joueur[tour%2]->ligne ++;
        break;
    case'E':
        joueur[tour%2]->colonne ++;
        break;
    case'W':
        joueur[tour%2]->colonne --;
        break;
    }
}

void positionner_pion(Joueur* joueur[2], Plateau* plateau,int tour)
{
    plateau->grille[joueur[tour%2]->ligne][joueur[tour%2]->colonne] = joueur[tour%2]->pion;
}

void attribution_point(Joueur* joueur[2],int tour)
{
    if (tour%2 == 1)
    {
        joueur[0]->victoires ++;
    }
    else
    {
        joueur[1]->victoires ++;
    }
}

void affichage_point(Joueur* joueur[2])
{
    gotoxy(73, 11);
    printf("Scores");
    gotoxy(70, 12);
    printf("Joueur 1: %d\n", joueur[0]->victoires);
    gotoxy(70, 13);
    printf("Joueur 2: %d\n", joueur[1]->victoires);
}

void detruire_joueurs(Joueur** adr_joueur)
{
    Joueur* joueur = *adr_joueur;
    free(joueur);
    *adr_joueur = NULL;
}

// Utiliation liste chainee
chained_list* create_chained()
{
    chained_list* liste = malloc(sizeof(chained_list)); //On créée la première structure de la liste, c'est elle qu'on utilisera pour manipuler la liste entière
    initialize_chained(liste, 0, 0, ' ');
    return liste;
}
void initialize_chained(chained_list* element, int ligne, int colonne, char pion)
{
    element->ligne = ligne;
    element->colonne = colonne;
    element->pion = pion;
    element->next = NULL;
}
void append_chained(chained_list* element, int ligne, int colonne, char pion)
{
    //On procède par récursivité. On va jusqu'au dernier élément de la liste en rapellant à chaque fois cette fonction avec l'objet suivant en argument
    if(element->next == NULL) //Si c'est le dernier élément, on lui ajoute un nouveau maillon
    {
        element->next = malloc(sizeof(chained_list));
        initialize_chained(element->next, ligne, colonne, pion);
    }
    else
    {
        append_chained(element->next, ligne, colonne, pion); //Sinon on va à l'élément suivant
    }
}
void destroy_chained(chained_list* element)
{
    //Là encore par récursivité. On détruit le dernier élément, puis celui juste avant, etc jusqu'à détruire en dernier le premier élément de la liste
    if(element->next != NULL)
    {
        destroy_chained(element->next);
    }
    free(element);
}

void rejouer_partie(chained_list* replay)
{
    clrscr();
    Plateau* plateau = creer_plateau(21, 21);
    chained_list* element = replay;
    int tour = 0;
    Joueur* joueurs[2];
    joueurs[0] = creer_joueur('A');
    joueurs[1] = creer_joueur('X');
    while(1)
    {
        //On fait une interface simplifiée
        textcolor(YELLOW);
        gotoxy(23, 3);
        printf("Les Pietons de tron [REPLAY]");
        textcolor(WHITE);
        afficher_plateau(plateau, joueurs);
        //À chaque tour on met à jour les coordonnées en prenant celles stockées dans le prochain élément de la liste
        joueurs[tour%2]->ligne = element->ligne;
        joueurs[tour%2]->colonne = element->colonne;
        Sleep(300);
        if(element->next != NULL) //S'il y a un élément suivant, alors il devient l'élément actuel et on recommence
        {
            positionner_pion(joueurs, plateau, tour);
            element = element->next;
        }
        else //Sinon c'est qu'on a atteint la fin du replay et donc que l'on s'arrête
        {
            joueurs[tour%2] -> ligne = -1;
            joueurs[tour%2] -> colonne = -1;
            break;
        }
        tour++;
    }
    //On affiche le plateau dans son état final
    clrscr();
    textcolor(YELLOW);
    gotoxy(23, 3);
    printf("Les Pietons de tron [REPLAY]");
    textcolor(WHITE);
    afficher_plateau(plateau, joueurs);
    //On détruit les éléments qui ont servi au replay
    detruire_plateau(&plateau);
    detruire_joueurs(&joueurs[0]);
    detruire_joueurs(&joueurs[1]);
}












