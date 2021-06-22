#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "tas.h"
#include "partition.h"
#include "liste.h"
#include "graphe.h"
#include "labyrinthe.h"

int main(){	
	srand(10);
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL; 

	SDL_Event event;
	SDL_Rect rect;

	int quit = 0;

	if (SDL_Init(SDL_INIT_VIDEO) == 0){

		window = SDL_CreateWindow("Labyrinthe",
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								1080,
								720,
								SDL_WINDOW_RESIZABLE);
		
		if (window == NULL) {
			SDL_Quit();
			exit(EXIT_FAILURE);
		}
		
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL) {
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(EXIT_FAILURE);
		}

		labyrinthe_t labyrinthe = init_labyrinthe(10, 15);

		while (!quit){
			SDL_PollEvent(&event);

			if (event.type == SDL_QUIT)
				quit = 1;

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect);

			afficher_labyrinthe(window ,renderer, labyrinthe);

			SDL_RenderPresent(renderer);
    	}
	}



	return 0;
}

/*data_t tab[] = {14, 4, 5, 10, 11, 23, 6, 12, 20};

	tri_tas(&tab, 9);
	for(int i=0; i<9; i++){
		printf("%d\n", tab[i]);
	}
	
	liste_t ** liste = NULL;
	partition_t partition;
	partition = init_partition(11);

	fusion_partition(0, 1, &partition);
	fusion_partition(2, 3, &partition);
	fusion_partition(10, 3, &partition);
	fusion_partition(5, 9, &partition);
	fusion_partition(4, 6, &partition);
	fusion_partition(8, 7, &partition);
	fusion_partition(9, 7, &partition);
	fusion_partition(6, 8, &partition);

	liste = liste_classes_partition(partition);
	afficher_table_partition(liste, partition.taille);

	liberer_table_partition(&liste, partition.taille);
	liberer_partition(&partition);

	//creer_affichage_partition(partition);

	graphe_t graphe = graphe_aleatoire(20, 30);
	graphe_t arbre_couv = kruskal(graphe);

	affichage_graphe(graphe, "./files/graphe.dot");
	affichage_graphe(arbre_couv, "./files/arbre_cou.dot");*/