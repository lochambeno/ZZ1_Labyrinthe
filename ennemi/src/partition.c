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

	if(classe1 != classe2){
		if(partition->hauteur[classe1] >= partition->hauteur[classe2]){
			partition->parent[classe2] = classe1;
			if(partition->hauteur[classe1] == partition->hauteur[classe2])
				partition->hauteur[classe1] += 1;
		}
		else{
			partition->parent[classe1] = classe2;
			//partition->hauteur[classe2] += 1;
		}
	}
}

liste_t * liste_el_classe_partition(int classe, partition_t partition){
	int 	i,
			classe_racine = classe_element_partition(classe, partition);
	liste_t * liste = creer_liste();
	
	for(i=0; i<partition.taille; i++){
		if(classe_element_partition(i, partition) == classe_racine){
			insertion(&liste, i);
		}
	}

	//afficher_liste(liste);

	return liste;
}

liste_t ** liste_classes_partition(partition_t partition){
	liste_t ** tableau_classes = NULL;
	int 	i,
			classe,
			erreur,
			erreur_fonction = 0;;

	tableau_classes = (liste_t**) malloc(sizeof(liste_t*)*partition.taille);
	if(tableau_classes != NULL){
		//initialisation du tableau de listes
		for(i=0; i<partition.taille; i++){
			tableau_classes[i] = creer_liste();
		}

		//calcul des classes elles-memes
		for(i=0; i<partition.taille; i++){
			classe = classe_element_partition(i, partition);

			erreur = insertion(&tableau_classes[classe], i);
			if(!erreur){
				erreur_fonction = 1;
			}
		}

		if(erreur_fonction){
			//liberer_tableau_partition
		}
	}	
	return tableau_classes;
}

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

void liberer_partition(partition_t * partition){
	free(partition->parent);
	free(partition->hauteur);
	partition->taille = 0;
}

void liberer_table_partition(liste_t *** table_part, int taille){
	for(int i=0; i<taille; i++){
		if((*table_part)[i] != NULL)
			liberer_liste(&((*table_part)[i]));
	}
	free(*table_part);
}

void afficher_table_partition(liste_t ** table_part, int taille){
	for(int i =0; i<taille; i++){
		if(table_part[i] != NULL){
			printf("Classe : %d\n", i);
			afficher_liste(table_part[i]);
			printf("\n");
		}
	}
}