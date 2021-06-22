#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "partition.h"


int main()
{	/*
	part_t part = init_part(11);

	fusion_part(&part, 0, 1);
	fusion_part(&part, 2, 3);
	fusion_part(&part, 10, 3);
	fusion_part(&part, 5, 9);
	fusion_part(&part, 4, 6);
	fusion_part(&part, 8, 7);
	fusion_part(&part, 9, 7);
	fusion_part(&part, 6, 8);

	liste_t** liste = lister_classes(part);


	afficher_part(part);

	liberer_classes(liste, part.taille);
	liberer_partition(&part);
	*/
	srand(2);
	graphe_t graphe = creer_graphe(10);
	init_graph(&graphe);
	afficher_graphe(graphe, "./file/aff_graphe.dot");
	/*
	part_t part  = graphe_part(graphe);
	compo_connexe(part, graphe, 5);
	*/
	
	graphe_t arbre = kruskal(graphe);
	printf("aaf %d\n",arbre.tab_arretes[4].b);
	afficher_graphe(arbre, "./file/aff_arbre.dot");


	return 0;
}