#ifndef ZZ1_PROJET_GRAPHE_H
#define ZZ1_PROJET_GRAPHE_H

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

#endif