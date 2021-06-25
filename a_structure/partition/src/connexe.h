#ifndef CONNEXE_H
#define CONNEXE_H
#include "partition.h"

typedef struct arrete_c {
    int A;
    int B;
} arrete_t;

typedef struct graphe_c {
    arrete_t* arrete;
    int nbr_noeuds;
    int nbr_arretes;
} graphe_t;

int** mat_adj(int);
part_t mat_comp_connexe(int**, int);
void afficher_graphe_mat(int**, int);
void afficher_mat(int**, int);
void liberer_mat(int**, int);

graphe_t init_graphe(int);
void ajouter_arrete(graphe_t*, int, int);
void afficher_graphe(graphe_t);
part_t graphe_comp_connexe(graphe_t);
void afficher_graphe_comp_connexe(graphe_t, int);
void liberer_graphe(graphe_t*);

#endif