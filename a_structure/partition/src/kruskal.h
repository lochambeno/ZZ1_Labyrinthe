#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "connexe.h"
#include "partition.h"

void echange_arrete(graphe_t*, int, int);
void fisher_yate(graphe_t*);
graphe_t kruskal(graphe_t);
void afficher_arbre_couvrant(graphe_t);

#endif