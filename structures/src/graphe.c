#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

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

void affichage_graphe(graphe_t graphe, char* adresse){
	int i;
	arrete_t arrete;
	FILE * fichier_dot = NULL;

	fichier_dot = fopen(adresse, "w+");
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

partition_t composantes_connexes(graphe_t graphe){
	partition_t partition = init_partition(graphe.nbr_noeuds);
	int i;
	arrete_t arrete;
	
	for(i=0; i<graphe.nbr_arretes; i++){
		arrete = graphe.table_arretes[i];
		fusion_partition(arrete.noeud1, arrete.noeud2, &partition);
	}

	return partition;
}

void sous_graphe_composante_connexe(graphe_t graphe, int noeud){
	//tableau permettant de stocker les arretes a afficher
	int nbr_arrete = 0;
	arrete_t * a_afficher = (arrete_t*) malloc(graphe.nbr_arretes * sizeof(arrete_t));
	//la partition permet de calculer les composantes connexes et d'avoir
	//acces aux noeuds dans une liste chainee
	partition_t cc = composantes_connexes(graphe);
	liste_t ** liste_classe = liste_classes_partition(cc);
	
	int classe_noeud = classe_element_partition(noeud, cc);

	int i;
	liste_t * cour = NULL;
	FILE * fichier_dot = NULL;

	//pour chaque arrete, on regarde si l'un des noeuds est dans la composante connexe
	if(a_afficher != NULL){
		for(i=0; i<graphe.nbr_arretes; i++){
			cour = liste_classe[classe_noeud];
			while(cour != NULL 	&& cour->val != graphe.table_arretes[i].noeud1){
				cour = cour->suiv;
			}

			if(cour != NULL){
				a_afficher[nbr_arrete] = graphe.table_arretes[i];
				nbr_arrete++;
			}
		}
	

		//creation du fichier .dot
		fichier_dot = fopen("./files/sous_graphe.dot", "w+");
		fprintf(fichier_dot, "graph {\n");

		for(i=0; i<nbr_arrete; i++){
			fprintf(fichier_dot, "\t%d -- %d;\n", a_afficher[i].noeud1, a_afficher[i].noeud2);
		}

		fprintf(fichier_dot, "}");
		fclose(fichier_dot);
		free(a_afficher);
	}
	//liberation
	liberer_table_partition(&liste_classe, cc.taille);
	liberer_partition(&cc);
}

graphe_t kruskal(graphe_t graphe){
	graphe_t arbre_cou = init_graphe(graphe.nbr_noeuds);
	partition_t partition = init_partition(graphe.nbr_noeuds);
	int i;
	int noeud1, noeud2;

	for(i=0; i<graphe.nbr_arretes; i++){
		noeud1 = graphe.table_arretes[i].noeud1;
		noeud2 = graphe.table_arretes[i].noeud2;

		if(classe_element_partition(noeud1, partition) !=
			classe_element_partition(noeud2, partition)){
			
			fusion_partition(noeud1, noeud2, &partition);
			ajouter_arrete_graphe(noeud1, noeud2, &arbre_cou);
		}
	}
	return arbre_cou;
}