#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "labyrinthe.h"
#include "tas_noeuds.h"

#define MAX_I 2147483647

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
		direction = 2;
	}
	else{
		if(i/largeur > j/largeur){
			direction = 1;
		}
		else{
			if(i%largeur < j%largeur){
				direction = 4;
			}
			else{
				if(i%largeur > j%largeur){
				direction = 8;
				}
			}
		}
	}

	return direction;
}

void init_mat_voisin_lab(labyrinthe_t * labyrinthe){
	int i;
	int noeud1, noeud2;

	for(i=0; i<labyrinthe->graph_lab.nbr_arretes; i++){
		noeud1 = labyrinthe->graph_lab.table_arretes[i].noeud1;
		noeud2 = labyrinthe->graph_lab.table_arretes[i].noeud2;

		//printf("Noeuds : %d , %d \n", noeud1, noeud2);

		labyrinthe->matrice_voisins[noeud1].direction += direction_labyrinthe(noeud1, noeud2, labyrinthe->largeur);
		labyrinthe->matrice_voisins[noeud2].direction += direction_labyrinthe(noeud2, noeud1, labyrinthe->largeur);

		//printf("Voisins : %d , %d \n", labyrinthe->matrice_voisins[noeud1], labyrinthe->matrice_voisins[noeud2]);
	}

}

labyrinthe_t init_labyrinthe(int hauteur, int largeur){
	labyrinthe_t labyrinthe;
	graphe_t retour;
	int i, j;

	labyrinthe.graph_lab = init_graphe(hauteur*largeur);
	labyrinthe.hauteur = hauteur;
	labyrinthe.largeur = largeur;

	labyrinthe.matrice_voisins = (case_t *) malloc(sizeof(case_t) * hauteur * largeur);

	for(i=0; i<hauteur*largeur; i++){
		labyrinthe.matrice_voisins[i].poids = 1;
		labyrinthe.matrice_voisins[i].direction = 0;
	}

	if(labyrinthe.matrice_voisins != NULL){
		for(i=0; i<hauteur; i++){
			for(j=0; j<largeur; j++){
				if(i+1 < hauteur)
					ajouter_arrete_graphe(i*largeur+j, (i+1)*largeur+j, 1, &(labyrinthe.graph_lab));
				
				if(j+1 < largeur)
					ajouter_arrete_graphe(i*largeur+j, i*largeur+j+1, 1, &(labyrinthe.graph_lab));
			}
		}

		fisher_yate(&labyrinthe);
		retour = kruskal(labyrinthe.graph_lab);
		
		liberer_graphe(&(labyrinthe.graph_lab));
		labyrinthe.graph_lab = retour;

		init_mat_voisin_lab(&labyrinthe);

	}
	else{
		labyrinthe.hauteur = 0;
		labyrinthe.largeur = 0;
	}

	return labyrinthe;
}

void afficher_labyrinthe_NB(SDL_Window * window, SDL_Renderer * renderer, labyrinthe_t labyrinthe){
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
	}
}

void afficher_texture_labyrinthe(SDL_Window * window, SDL_Texture * texture, SDL_Renderer * renderer, labyrinthe_t labyrinthe){
	int i;

	SDL_Rect 	source = {0},
				window_dimension = {0},
				destination = {0};

	SDL_GetWindowSize(window, &window_dimension.w, &window_dimension.h);
	SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);

	source.h = source.h/8;
	source.w = source.w/12;

	destination.h = window_dimension.h/labyrinthe.hauteur;
	destination.w = window_dimension.w/labyrinthe.largeur;

	//1:N ; 2:S ; 4:E ; 8:O
	for(i=0; i<labyrinthe.hauteur * labyrinthe.largeur; i++){
		destination.x = i%labyrinthe.largeur * destination.w;
		destination.y = i/labyrinthe.largeur * destination.h;

		switch(labyrinthe.matrice_voisins[i].direction){

		//cul de sac
		case 1:
			source.x = 9*source.w;
			source.y = 2*source.h;
			break;

		case 2:
			source.x = 8*source.w;
			source.y = 2*source.h;
			break;

		case 4:
			source.x = 8*source.w;
			source.y = 3*source.h;			
			break;

		case 8:
			source.x = 9*source.w;
			source.y = 3*source.h;
			break;
		
		//2 directions
		case 3:
			source.x = 0*source.w;
			source.y = 0*source.h;
			break;

		case 5:
			source.x = 5*source.w;
			source.y = 1*source.h;
			break;

		case 9:
			source.x = 6*source.w;
			source.y = 1*source.h;
			break;

		case 6:
			source.x = 5*source.w;
			source.y = 0*source.h;
			break;

		case 10:
			source.x = 6*source.w;
			source.y = 0*source.h;
			break;

		case 12:
			source.x = 0*source.w;
			source.y = 1*source.h;
			break;
		
		//Les T
		case 7:
			source.x = 4*source.w;
			source.y = 2*source.h;
			break;

		case 11:
			source.x = 5*source.w;
			source.y = 2*source.h;
			break;

		case 13:
			source.x = 4*source.w;
			source.y = 3*source.h;
			break;

		case 14:
			source.x = 5*source.w;
			source.y = 3*source.h;
			break;

		//Les quatre directions
		case 15:
			source.x = 9*source.w;
			source.y = 0*source.h;
			break;
		
		default:
			source.x = 0*source.w;
			source.y = 2*source.h;
			break;
		}

		SDL_RenderCopy(renderer, texture, &source, &destination);
	}
}

void liberer_labyrinthe(labyrinthe_t * labyrinthe){
	liberer_graphe(&(labyrinthe->graph_lab));
	free(labyrinthe->matrice_voisins);
	labyrinthe->hauteur = 0;
	labyrinthe->largeur = 0;
}

void modifier_tas_lab(noeud_t nouveau_noeud, tas_t * tas, int ** noeuds_tas){
	int i = (*noeuds_tas)[nouveau_noeud.id_noeud];

	tas->tas[i].parent = nouveau_noeud.parent;
	tas->tas[i].poids = nouveau_noeud.poids;

	while(tas->tas[i].poids < tas->tas[parent(i)].poids){
			echange(&(tas->tas[i]), &(tas->tas[parent(i)]));

			(*noeuds_tas)[tas->tas[i].id_noeud] = parent(i);
			(*noeuds_tas)[tas->tas[parent(i)].id_noeud] = i;

			i = parent(i);
	}
}

//recupere le noeud au dessus du tas et ajoute les noeuds qui lui sont
//adjacent
void ajout_noeuds_tas(labyrinthe_t labyrinthe, tas_t * tas, int ** noeuds_tas){
	noeud_t a_traite = *sommet_tas(tas);
	noeud_t a_inserer;
	int direction = labyrinthe.matrice_voisins[a_traite.id_noeud].direction;

	supprimer_tas(tas, noeuds_tas);

	//1:N ; 2:S ; 4:E ; 8:O
	if(direction & 1){
		a_inserer.id_noeud = a_traite.id_noeud - labyrinthe.largeur;
		a_inserer.parent = a_traite.id_noeud;
		a_inserer.poids = a_traite.poids + labyrinthe.matrice_voisins[a_inserer.id_noeud].poids;

		if((*noeuds_tas)[a_inserer.id_noeud] == -1)
				inserer_tas(tas, a_inserer, noeuds_tas);
		else{
			if((*noeuds_tas)[a_inserer.id_noeud] != -2 && a_inserer.poids < tas->tas[(*noeuds_tas)[a_inserer.id_noeud]].poids)
				modifier_tas_lab(a_inserer, tas, noeuds_tas);
		}
	}

	if(direction & 2){
		a_inserer.id_noeud = a_traite.id_noeud + labyrinthe.largeur;
		a_inserer.parent = a_traite.id_noeud;
		a_inserer.poids = a_traite.poids + labyrinthe.matrice_voisins[a_inserer.id_noeud].poids;

		if((*noeuds_tas)[a_inserer.id_noeud] == -1)
				inserer_tas(tas, a_inserer, noeuds_tas);
		else{
			if((*noeuds_tas)[a_inserer.id_noeud] != -2 && a_inserer.poids < tas->tas[(*noeuds_tas)[a_inserer.id_noeud]].poids)
				modifier_tas_lab(a_inserer, tas, noeuds_tas);
		}
	}

	if(direction & 4){
		a_inserer.id_noeud = a_traite.id_noeud + 1;
		a_inserer.parent = a_traite.id_noeud;
		a_inserer.poids = a_traite.poids + labyrinthe.matrice_voisins[a_inserer.id_noeud].poids;

		if((*noeuds_tas)[a_inserer.id_noeud] == -1)
				inserer_tas(tas, a_inserer, noeuds_tas);
		else{
			if((*noeuds_tas)[a_inserer.id_noeud] != -2 && a_inserer.poids < tas->tas[(*noeuds_tas)[a_inserer.id_noeud]].poids)
				modifier_tas_lab(a_inserer, tas, noeuds_tas);
		}
	}

	if(direction & 8){
		a_inserer.id_noeud = a_traite.id_noeud - 1;
		a_inserer.parent = a_traite.id_noeud;
		a_inserer.poids = a_traite.poids + labyrinthe.matrice_voisins[a_inserer.id_noeud].poids;

		if((*noeuds_tas)[a_inserer.id_noeud] == -1)
				inserer_tas(tas, a_inserer, noeuds_tas);
		else{
			if((*noeuds_tas)[a_inserer.id_noeud] != -2 && a_inserer.poids < tas->tas[(*noeuds_tas)[a_inserer.id_noeud]].poids)
				modifier_tas_lab(a_inserer, tas, noeuds_tas);
		}
	}
}

//noeuds dans le tas : (-1 : pas decouvert ; -2 : explore ; sinon index)
noeud_t * dijkstra(labyrinthe_t labyrinthe, int depart){
	tas_t tas = init_tas(10);
	int * noeuds_tas = NULL;

	noeud_t a_traite;
	noeud_t * table_noeuds = NULL;

	int nbr_traites = 0, 
		i,
		taille = labyrinthe.hauteur * labyrinthe.largeur;

	noeuds_tas = (int*) malloc(sizeof(int) * taille);
	table_noeuds = (noeud_t*) malloc(sizeof(noeud_t) * taille);

	if(noeuds_tas != NULL && table_noeuds != NULL){
		//initialisation de la matrice et du tas
		for(i=0; i<taille; i++){
			noeuds_tas[i] = -1;
		}
		
		a_traite.id_noeud = depart;
		a_traite.parent = depart;
		a_traite.poids = 0;

		inserer_tas(&tas, a_traite, &noeuds_tas);

		while(nbr_traites < taille){
			table_noeuds[nbr_traites] = *sommet_tas(&tas);
			
			//ajoute les noeuds dans le tas 
			ajout_noeuds_tas(labyrinthe, &tas, &noeuds_tas);

			//on l'insere dans la table des noeuds a son adresse
			
		}
	}

	return table_noeuds;
}