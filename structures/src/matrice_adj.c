#include <stdio.h>
#include <stdlib.h>

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



int main(){
	srand(1);

	int ** matrice = init_matrice_adjacence(10);
	creer_affichage_matrice(matrice, 10);

	return 0;
}