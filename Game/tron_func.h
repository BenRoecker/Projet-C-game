#ifndef TRON_FUNC_H_INCLUDED
#define TRON_FUNC_H_INCLUDED

typedef struct Plateau
{
    int lignes;
    int colonnes;
    char** grille;
} Plateau;

typedef struct Joueur
{
    int colonne;
    int ligne;
    int victoires;
    char pion;
} Joueur;

typedef struct chained_list chained_list;

struct chained_list{
    int ligne;
    int colonne;
    char pion;
    chained_list* next;
};

Plateau* creer_plateau(int lignes, int colonnes);
Joueur* creer_joueur(char pions);
void afficher_plateau(Plateau* plateau, Joueur* joueur[2]);
void pos_initial(Joueur* joueur, int nombre, Plateau* plateau);
int defaite(Joueur* joueur[2], Plateau* plateau,int tour);
void initialiser_plateau(Plateau* plateau);
void affichage(Joueur* joueur[2], Plateau* plateau, int tour);
void affichage_defaite(Joueur* joueur[2], Plateau* plateau, int tour);
void obtenir_entree(Joueur* joueur[2],int tour);
void positionner_pion(Joueur* joueur[2], Plateau* plateau,int tour);
void attribution_point(Joueur* joueur[2],int tour);
void affichage_point(Joueur* joueur[2]);
void detruire_plateau(Plateau** adr_plateau);
void detruire_joueurs(Joueur** adr_joueur);

chained_list* create_chained();
void initialize_chained(chained_list* element, int ligne, int colonne, char pion);
void append_chained(chained_list* element, int ligne, int colonne, char pion);
void destroy_chained(chained_list* element);

void rejouer_partie(chained_list* replay);


#endif // TRON_FUNC_H_INCLUDED
