#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "tas_noeuds.h"
#include "partition.h"
#include "liste.h"
#include "graphe.h"
#include "labyrinthe.h"

int main(){	
	srand(1);
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL; 
	SDL_Texture * bg_texture = NULL;

	SDL_Event event;
	//SDL_Rect rect;

	labyrinthe_t labyrinthe = init_labyrinthe(20, 30);
	int quit = 0;
	noeud_t * table_noeud = NULL;

	//Initialisation de la SDL2
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

		bg_texture = IMG_LoadTexture(renderer, "./images/roadTextures_tilesheet@2.png");
		if(bg_texture == NULL){
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(EXIT_FAILURE);
		}

		//Boucle d'evenements
		while (!quit){
			while(!quit && SDL_PollEvent(&event)){
				if (event.type == SDL_QUIT)
					quit = 1;
			}

			//Affichage du labyrinthe
			afficher_texture_labyrinthe(window, bg_texture ,renderer, labyrinthe);

			SDL_RenderPresent(renderer);
    	}
	}

	table_noeud = dijkstra(labyrinthe, 0);
	afficher_liste(liste_chemin_court(table_noeud, 0, 1000));

	liberer_labyrinthe(&labyrinthe);

	SDL_DestroyTexture(bg_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}