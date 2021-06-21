#include <stdio.h>
#include <stdlib.h>
#include "partition.h"

partition_t init_partition(int taille){
	partition_t partition;
	int i;

	partition.parent = NULL;
	partition.hauteur = NULL;
	partition.taille = taille;
	
	partition.parent = (int*) malloc(taille*sizeof(int));

	if(partition.parent != NULL){
		partition.hauteur = (int*) malloc(taille*sizeof(int));

		if(partition.hauteur == NULL){
			free(partition.parent);
			partition.parent = NULL;
		}
	}

	if(partition.parent == NULL){
		partition.taille = 0;
	}
	else{
		for(i=0; i<taille; i++){
			partition.hauteur[i] = 1;
			partition.parent[i] = i;
		}
	}

	return partition;
}

int classe_element_partition(int id_element, partition_t partition){
	int cour = id_element;

	while(cour != partition.parent[cour]){
		cour = partition.parent[cour];
	}
	return cour;
}

void fusion_partition(int el1, int el2, partition_t * partition){
	int 	classe1 = classe_element_partition(el1, *partition),
			classe2 = classe_element_partition(el2, *partition);

	if(partition->hauteur[classe1] >= partition->hauteur[classe2]){
		partition->parent[classe2] = classe1;
		if(partition->hauteur[classe1] == partition->hauteur[classe2])
			partition->hauteur[classe1] += 1;
	}
	else{
		partition->parent[classe1] = classe2;
		partition->hauteur[classe2] += 1;
	}
}

/*int * liste_classes_partition(int, partition_t){

}*/

void creer_affichage_partition(partition_t partition){
	FILE * fichier_dot = NULL;
	int i;

	fichier_dot = fopen("./files/affichage.dot", "w+");

	if(fichier_dot != NULL){
		fprintf(fichier_dot, "digraph {\n");

		for(i=0; i<partition.taille; i++){
			fprintf(fichier_dot, "\t%d -> %d;\n", i, partition.parent[i]);
		}

		fprintf(fichier_dot, "}");

		fclose(fichier_dot);
	}
}
