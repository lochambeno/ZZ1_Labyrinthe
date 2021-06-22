#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "labyrinthe.h"

//melange les arretes d'un labyrinthe
// A REFAIRE
void fisher_yate(labyrinthe_t * labyrinthe){
	arrete_t * permuttation = (arrete_t*) malloc(labyrinthe->graph_lab.nbr_arretes*sizeof(arrete_t));
	//int nbr_permuttation = labyrinthe->nbr_arretes;
	int i, alea;

	for(i=0; i<labyrinthe->graph_lab.nbr_arretes; i++){
		//on prend une valeur aleatoire parmis les valeurs restantes dans le labyrinthe
		if(labyrinthe->graph_lab.nbr_arretes-1-i > 0)
			alea = rand()%(labyrinthe->graph_lab.nbr_arretes-1-i);
		else
			alea = 0;
		
		permuttation[i] = labyrinthe->graph_lab.table_arretes[alea];
		labyrinthe->graph_lab.table_arretes[alea] = labyrinthe->graph_lab.table_arretes[labyrinthe->graph_lab.nbr_arretes-1-i];
	}

	free(labyrinthe->graph_lab.table_arretes);
	labyrinthe->graph_lab.table_arretes = permuttation;
}

//renvois la direction dans laquelle va l'arrete de i vers j
//1:N ; 2:S ; 4:E ; 8:O
int direction_labyrinthe(int i, int j, int largeur){
	int direction = 0;

	if(i/largeur < j/largeur){
		direction += 2;
	}
	else{
		if(i/largeur > j/largeur){
			direction += 1;
		}
	}

	if(i%largeur < j%largeur){
		direction += 4;
	}
	else{
		if(i/largeur > j/largeur){
			direction += 8;
		}
	}

	return direction;
}

//
labyrinthe_t init_labyrinthe(int hauteur, int largeur){
	labyrinthe_t labyrinthe;
	graphe_t retour;
	int i, j;

	labyrinthe.graph_lab = init_graphe(hauteur*largeur);
	labyrinthe.hauteur = hauteur;
	labyrinthe.largeur = largeur;

	labyrinthe.matrice_voisins = NULL;//(int *) malloc(sizeof(int) * hauteur * largeur);

	//if(labyrinthe.matrice_voisins != NULL){
		for(i=0; i<hauteur; i++){
			for(j=0; j<largeur; j++){
				if(i+1 < hauteur)
					ajouter_arrete_graphe(i*largeur+j, (i+1)*largeur+j, &(labyrinthe.graph_lab));

				
				if(j+1 < largeur)
					ajouter_arrete_graphe(i*largeur+j, i*largeur+j+1, &(labyrinthe.graph_lab));
			}
		}

		fisher_yate(&labyrinthe);
		retour = kruskal(labyrinthe.graph_lab);
		
		//attention fuite de memoire !!!!
		labyrinthe.graph_lab = retour;
	/*}
	else{
		labyrinthe.hauteur = 0;
		labyrinthe.largeur = 0;
	}*/

	printf("%d, %d\n", labyrinthe.hauteur, labyrinthe.largeur);

	return labyrinthe;
}

void afficher_labyrinthe(SDL_Window * window, SDL_Renderer * renderer, labyrinthe_t labyrinthe){
	int i, noeud1, noeud2;
	int case_w, case_h;

	SDL_Rect rect1;

	SDL_GetWindowSize(window, &case_w, &case_h);
	case_w = case_w/labyrinthe.largeur;
	case_h = case_h/labyrinthe.hauteur;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for(i=0; i<labyrinthe.graph_lab.nbr_arretes; i++){

		noeud1 = labyrinthe.graph_lab.table_arretes[i].noeud1;
		noeud2 = labyrinthe.graph_lab.table_arretes[i].noeud2;

		if(noeud1/labyrinthe.largeur < noeud2/labyrinthe.largeur){
			rect1.y = noeud1/labyrinthe.largeur * case_h + (case_h/4);
			rect1.h = (noeud2-noeud1)/labyrinthe.largeur * case_h + (case_h/2);
		}
		else{
			if(noeud1/labyrinthe.largeur > noeud2/labyrinthe.largeur){
				rect1.y = noeud2/labyrinthe.largeur * case_h + (case_h/4);
				rect1.h = (noeud1-noeud2)/labyrinthe.largeur * case_h + (case_h/2) ;
			}
			else{
				rect1.y = noeud1/labyrinthe.largeur * case_h + (case_h/4);
				rect1.h = case_h/2;
			}
		}
		
		if(noeud1%labyrinthe.largeur < noeud2%labyrinthe.largeur){
			rect1.x = noeud1%labyrinthe.largeur * case_w + (case_w/4);
			rect1.w = (noeud2-noeud1)%labyrinthe.largeur * case_w + (case_w/2);
		}
		else{
			if(noeud1%labyrinthe.largeur > noeud2%labyrinthe.largeur){
				rect1.x = noeud2%labyrinthe.largeur * case_w + (case_w/4);
				rect1.w = (noeud1-noeud2)%labyrinthe.largeur * case_w + (case_w/2);
			}
			else{
				rect1.x = noeud1%labyrinthe.largeur * case_w + (case_w/4);
				rect1.w = case_w/2;
			}
		}

		SDL_RenderFillRect(renderer, &rect1);
		

		/*x1 = noeud1%10 * 108;
		y1 = noeud1/10 * 72;

		x2 = noeud2%10 * 108 ;
		y2 = noeud2/10 * 72;*/

		//SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	}
}