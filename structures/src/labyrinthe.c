#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "labyrinthe.h"

//melange les arretes d'un labyrinthe
void fisher_yate(labyrinthe_t * labyrinthe){
	arrete_t * permuttation = (arrete_t*) malloc(labyrinthe->nbr_arretes*sizeof(arrete_t));
	//int nbr_permuttation = labyrinthe->nbr_arretes;
	int i, alea;

	for(i=0; i<labyrinthe->nbr_arretes; i++){
		//on prend une valeur aleatoire parmis les valeurs restantes dans le labyrinthe
		if(labyrinthe->nbr_arretes-1-i > 0)
			alea = rand()%(labyrinthe->nbr_arretes-1-i);
		else
			alea = 0;
		
		permuttation[i] = labyrinthe->table_arretes[alea];
		labyrinthe->table_arretes[alea] = labyrinthe->table_arretes[labyrinthe->nbr_arretes-1-i];
	}

	free(labyrinthe->table_arretes);
	labyrinthe->table_arretes = permuttation;
}

labyrinthe_t init_labyrinthe(int hauteur, int largeur){
	labyrinthe_t labyrinthe_temp = init_graphe(hauteur*largeur);
	labyrinthe_t retour;
	int i, j;

	for(i=0; i<hauteur; i++){
		for(j=0; j<largeur; j++){
			if(i+1 < hauteur)
				ajouter_arrete_graphe(i*largeur+j, (i+1)*largeur+j, &labyrinthe_temp);
			
			if(j+1 < largeur)
				ajouter_arrete_graphe(i*largeur+j, i*largeur+j+1, &labyrinthe_temp);
		}
	}

	fisher_yate(&labyrinthe_temp);
	retour = kruskal(labyrinthe_temp);

	return retour;

}