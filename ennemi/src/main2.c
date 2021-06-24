#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "tas_noeuds.h"
#include "partition.h"
#include "liste.h"
#include "graphe.h"
#include "labyrinthe.h"
#include "ennemi.h"

#define N 10
#define M 15

int main(){	
	srand(1);
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL; 
	SDL_Texture * bg_texture = NULL;
	SDL_Texture ** table_ennemi_G = NULL;
    SDL_Texture ** table_ennemi_D = NULL;


	SDL_Event event;

	labyrinthe_t labyrinthe = init_labyrinthe(N, M);
	int quit = 0, position_ennemi, direction_ennemi = 1, destination = 0, orientation_ennemi = 1, state=0;
	noeud_t * table_noeud = NULL;
	liste_t * cour_chemin = creer_liste();
	liste_t * cour = NULL;



	//Initialisation de la SDL2
	if (SDL_Init(SDL_INIT_VIDEO) == 0){

		window = SDL_CreateWindow("Labyrinthe",
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								1080,
								720,
								0);
		
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

		table_ennemi_D = (SDL_Texture **) malloc(sizeof(SDL_Texture*) * 4);
		table_ennemi_G = (SDL_Texture **) malloc(sizeof(SDL_Texture*) * 4);

		table_ennemi_G[0] = IMG_LoadTexture(renderer, "./images/SkeletonG_1.png");
        table_ennemi_G[1] = IMG_LoadTexture(renderer, "./images/SkeletonG_2.png");
        table_ennemi_G[2] = IMG_LoadTexture(renderer, "./images/SkeletonG_3.png");
        table_ennemi_G[3] = IMG_LoadTexture(renderer, "./images/SkeletonG_4.png");


        table_ennemi_D[0] = IMG_LoadTexture(renderer, "./images/SkeletonD_1.png");
        table_ennemi_D[1] = IMG_LoadTexture(renderer, "./images/SkeletonD_2.png");
        table_ennemi_D[2] = IMG_LoadTexture(renderer, "./images/SkeletonD_3.png");
        table_ennemi_D[3] = IMG_LoadTexture(renderer, "./images/SkeletonD_4.png");



		position_ennemi = 0;

		cour = cour_chemin;


		//Boucle d'evenements
		while (!quit){
			while(!quit && SDL_PollEvent(&event)){
				if (event.type == SDL_QUIT)
					quit = 1;
			}

			//Affichage du labyrinthe
			afficher_texture_labyrinthe(window, bg_texture ,renderer, labyrinthe);


			
            afficher_ennemi(position_ennemi, N, M, direction_ennemi, table_ennemi_D, table_ennemi_G,state, &orientation_ennemi, renderer, window);
            if (!state%4) {
                if(cour != NULL && cour->suiv != NULL && destination != position_ennemi){

                    direction_ennemi = direction_labyrinthe(position_ennemi, cour->val, M);

                    position_ennemi = cour->val;
                                        cour = cour->suiv;
                }
                else{
                    if(cour != NULL)
                        liberer_liste(&cour_chemin);

                    free(table_noeud);

                    
                    destination = rand()%(N*M);

                    //table_noeud = a_star(labyrinthe, position_ennemi, destination, 1);
                    table_noeud = dijkstra(labyrinthe, position_ennemi);

                    cour_chemin = liste_chemin_court(table_noeud, position_ennemi, destination);
                    


                    cour = cour_chemin;
                }
            }
            state=(state+1)%4;
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