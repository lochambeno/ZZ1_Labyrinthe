#ifndef ZZ1_PROJET_GRAPHE_H
#define ZZ1_PROJET_GRAPHE_H
#include "partition.h"



typedef struct arrete_c{

    int a;
    int b;

}arrete_t;


typedef struct graphe_c{

    arrete_t* tab_arretes;
    int nbr_arretes;
    int taille_tab;
    int nbr_noeuds;

}graphe_t;

graphe_t creer_graphe(int);
void creer_arrete(graphe_t* , int , int);
void init_graph(graphe_t*);
void afficher_graphe(graphe_t, char*);
part_t graphe_part(graphe_t);
int in_liste(liste_t , int);
void compo_connexe(part_t , graphe_t , int);
graphe_t kruskal(graphe_t);


#endif