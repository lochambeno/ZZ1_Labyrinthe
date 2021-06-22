#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "partition.h"

//il faut verifier la taille du graphe ou le tableau apres initialisation
graphe_t init_graphe(int nbr_noeuds){
	graphe_t graphe;

	graphe.nbr_arretes = 0;
	graphe.nbr_noeuds = nbr_noeuds;
	graphe.table_arretes = (arrete_t*) malloc(10*sizeof(arrete_t));

	if(graphe.table_arretes != NULL){
		graphe.taille = 10;
	}
	else{
		graphe.taille = 0;
	}

	return graphe;
}

void ajouter_noeud_graphe(int nbr_noeuds, graphe_t * graphe){
	graphe->nbr_noeuds += nbr_noeuds;
}

void ajouter_arrete_graphe(int noeud1, int noeud2, graphe_t * graphe){
	int nouvelle_taille;
	arrete_t * temp = NULL;

	if(graphe->taille != 0){
		arrete_t arrete;

		//on gere la potentielle reallocation
		if(graphe->nbr_arretes >= graphe->taille){
			nouvelle_taille = 1.5 * graphe->taille;

			temp = (arrete_t *) realloc(graphe->table_arretes, nouvelle_taille * sizeof(arrete_t));
			
			if(temp != NULL){
				graphe->table_arretes = temp;
				graphe->taille = nouvelle_taille;
			}
		}

		//on reverifie dans le cas ou la reallocation echoue
		if(graphe->nbr_arretes < graphe->taille){
			arrete.noeud1 = noeud1;
			arrete.noeud2 = noeud2;
			
			graphe->table_arretes[graphe->nbr_arretes] = arrete;
			graphe->nbr_arretes += 1;
		}
	}
}

void affichage_graphe(graphe_t graphe){
	int i;
	arrete_t arrete;
	FILE * fichier_dot = NULL;

	fichier_dot = fopen("./files/graphe.dot", "w+");
	fprintf(fichier_dot, "graph {\n");

	for(i=0; i<graphe.nbr_noeuds; i++){
		fprintf(fichier_dot, "\t%d;\n", i);
	}

	for(i=0; i<graphe.nbr_arretes; i++){
		arrete = graphe.table_arretes[i];
		fprintf(fichier_dot, "\t%d -- %d;\n", arrete.noeud1, arrete.noeud2);
	}

	fprintf(fichier_dot, "}");
	fclose(fichier_dot);
}

graphe_t graphe_aleatoire(int taille, int nbr_arrete){
	int i;
	graphe_t graphe = init_graphe(taille);

	for(i=0; i<nbr_arrete; i++){
		ajouter_arrete_graphe(rand()%taille, rand()%taille, &graphe);
	}

	return graphe;
}
/*
partition_t composantes_connexes(graphe_t graphe){

}*/