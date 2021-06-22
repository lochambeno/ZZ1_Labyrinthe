#include <stdio.h>
#include <stdlib.h>
#include "partition.h"
#include "liste.h"

int ** init_matrice_adjacence(int n){
	int ** matrice = NULL;
	int * arrete = NULL;

	int i, j;

	matrice = (int**) malloc(n*sizeof(int*));
	arrete = (int*) malloc(n*sizeof(int));
	if(matrice != NULL && arrete != NULL){
		for(i=0; i<n; i++){
			matrice[i] = (int*) malloc(n*sizeof(int*));
			arrete[i] = 0;
		}

		for(i=0; i<n; i++){			
			for(j=i; j<n; j++){
				if(j == i){
					matrice[i][j] = 1;
				}
				else{
					if(arrete[i] < 4 && arrete[j] < 4){
						matrice[i][j] = rand()%2;
						matrice[j][i] = matrice[i][j];
						arrete[i] += 1;
						arrete[j] += 1;
					}
				}
			}
		}
	}

	return matrice;
}

void creer_affichage_matrice(int ** matrice, int n){
	int i, j;
	FILE * fichier_dot = NULL;

	fichier_dot = fopen("./files/matrice.dot", "w+");

	if(fichier_dot != NULL){
		fprintf(fichier_dot, "graph {\n");

		for(i=0; i<n; i++){
			fprintf(fichier_dot, "\t%d;\n", i);
			for(j=i+1; j<n; j++){
				if(matrice[i][j] == 1)
					fprintf(fichier_dot, "\t%d -- %d;\n", i, j);
			}
		}

		fprintf(fichier_dot, "}");
		fclose(fichier_dot);
	}
}

partition_t composante_connexe_matrice(int ** matrice, int taille){
	int i, j;
	partition_t partition = init_partition(taille);
	liste_t ** table_classe = NULL;

	for(i=0; i<taille; i++){
		for(j=i+1; j<taille; j++){
			if(matrice[i][j] == 1){
				fusion_partition(i, j, &partition);
			}
		}
	}

	table_classe = liste_classes_partition(partition);
	afficher_table_partition(table_classe, taille);
	liberer_table_partition(&table_classe, taille);

	return partition;
}

int main(){
	srand(1);

	partition_t partition;
	int ** matrice = init_matrice_adjacence(10);
	creer_affichage_matrice(matrice, 10);

	partition = composante_connexe_matrice(matrice, 10);
	creer_affichage_partition(partition);

	return 0;
}