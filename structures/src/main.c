#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "tas_noeuds.h"
#include "partition.h"
#include "liste.h"
#include "graphe.h"
#include "labyrinthe.h"
#include "voiture.h"

#define N 20
#define M 30

int main(){	
	srand(10);
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL; 
	SDL_Texture * bg_texture = NULL;
	SDL_Texture ** table_voiture = NULL;

	SDL_Event event;
	//SDL_Rect rect;

	labyrinthe_t labyrinthe = init_labyrinthe(N, M);
	int quit = 0, position_voiture, direction_voiture = 1, destination = 0, depart;
	noeud_t * table_noeud = NULL;
	liste_t * cour_chemin = creer_liste();
	liste_t * cour = NULL;

	SDL_Rect 	destination_rect = {0},
				origine_rect = {0};

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

		table_voiture = (SDL_Texture **) malloc(sizeof(SDL_Texture*) * 4);

		table_voiture[0] = IMG_LoadTexture(renderer, "./images/rounded_red_right.png");
		table_voiture[1] = IMG_LoadTexture(renderer, "./images/rounded_red_left.png");
		table_voiture[2] = IMG_LoadTexture(renderer, "./images/rounded_red_up.png");
		table_voiture[3] = IMG_LoadTexture(renderer, "./images/rounded_red_down.png");

		position_voiture = 0;
		depart = position_voiture;

		cour = cour_chemin;

		destination_rect.w = 1080/M;
		destination_rect.h = 720/N;

		origine_rect.w = 1080/M;
		origine_rect.h = 720/N;

		//Boucle d'evenements
		while (!quit){
			while(!quit && SDL_PollEvent(&event)){
				if (event.type == SDL_QUIT)
					quit = 1;
			}

			//Affichage du labyrinthe
			afficher_texture_labyrinthe(window, bg_texture ,renderer, labyrinthe);

			//affichage destination
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &destination_rect);

			//affichage origine
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			SDL_RenderFillRect(renderer, &origine_rect);
			
			afficher_voiture(position_voiture, direction_voiture, N, M, table_voiture, renderer, window);

			if(cour != NULL && cour->suiv != NULL && destination != position_voiture){
				cour = cour->suiv;

				direction_voiture = direction_labyrinthe(position_voiture, cour->val, M);

				position_voiture = cour->val;
			}
			else{
				if(cour != NULL)
					liberer_liste(&cour_chemin);

				free(table_noeud);

				table_noeud = dijkstra(labyrinthe, position_voiture);
				destination = rand()%(N*M);
				cour_chemin = liste_chemin_court(table_noeud, position_voiture, destination);
				
				origine_rect.x = destination_rect.x;
				origine_rect.y = destination_rect.y;

				destination_rect.x = destination_rect.w * (destination % M);
				destination_rect.y = destination_rect.h * (destination / M);

				cour = cour_chemin;
			}

			SDL_RenderPresent(renderer);
			SDL_Delay(100);
    	}
	}

	liberer_liste(&cour_chemin);
	liberer_labyrinthe(&labyrinthe);

	SDL_DestroyTexture(bg_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}