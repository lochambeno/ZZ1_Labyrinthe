#ifndef ZZ1_PROJET_GRAPHE_H
#define ZZ1_PROJET_GRAPHE_H

#include "partition.h"

typedef struct arrete_c{
	int noeud1;
	int noeud2;
	//int direction;
}arrete_t;

typedef struct graphe_c{
	int nbr_noeuds;
	int nbr_arretes;
	int taille;
	arrete_t * table_arretes;
}graphe_t;

graphe_t init_graphe(int);
void ajouter_noeud_graphe(int, graphe_t *);
void ajouter_arrete_graphe(int, int, graphe_t *);
void affichage_graphe(graphe_t, char*);
graphe_t graphe_aleatoire(int , int );
partition_t composantes_connexes(graphe_t);

//algorithmes
graphe_t kruskal(graphe_t graphe);

void sous_graphe_composante_connexe(graphe_t graphe, int noeud);

#endif