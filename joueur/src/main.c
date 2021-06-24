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
#include "voiture.h"
#include "joueur.h"
#include "piece.h"

#define N 10
#define M 15

int main(){	
	srand(1);
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL; 
	SDL_Texture * bg_texture = NULL;
	SDL_Texture ** table_voiture = NULL,
				** joueur_D = NULL,
				** joueur_G = NULL,
				** texture_joueur = NULL,
				** piece = NULL,
				** mur = NULL;

	SDL_Event event;
	//SDL_Rect rect;

	labyrinthe_t labyrinthe = init_labyrinthe(N, M);
	int quit = 0, position_joueur = 0, abouge=0, state = 0, position_piece=rand()%(N*M);
	noeud_t * table_noeud = NULL;
	liste_t * cour_chemin = creer_liste();
	liste_t * cour = NULL;

	SDL_Rect 	destination_rect = {0},
				origine_rect = {0};

	//clock_t debut, fin;

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
		/*
		table_voiture = (SDL_Texture **) malloc(sizeof(SDL_Texture*) * 4);

		table_voiture[0] = IMG_LoadTexture(renderer, "./images/rounded_red_right.png");
		table_voiture[1] = IMG_LoadTexture(renderer, "./images/rounded_red_left.png");
		table_voiture[2] = IMG_LoadTexture(renderer, "./images/rounded_red_up.png");
		table_voiture[3] = IMG_LoadTexture(renderer, "./images/rounded_red_down.png");
		*/
		joueur_D = (SDL_Texture **) malloc(sizeof(SDL_Texture*) * 4);
		joueur_D[0] = IMG_LoadTexture(renderer, "./images/JoueurD_1.png");
		joueur_D[1] = IMG_LoadTexture(renderer, "./images/JoueurD_2.png");
		joueur_D[2] = IMG_LoadTexture(renderer, "./images/JoueurD_3.png");
		joueur_D[3] = IMG_LoadTexture(renderer, "./images/JoueurD_4.png");


		joueur_G = (SDL_Texture **) malloc(sizeof(SDL_Texture*) * 4);
		joueur_G[0] = IMG_LoadTexture(renderer, "./images/JoueurG_1.png");
		joueur_G[1] = IMG_LoadTexture(renderer, "./images/JoueurG_2.png");
		joueur_G[2] = IMG_LoadTexture(renderer, "./images/JoueurG_3.png");
		joueur_G[3] = IMG_LoadTexture(renderer, "./images/JoueurG_4.png");

		piece = (SDL_Texture **) malloc(sizeof(SDL_Texture*) * 4);
		piece[0] = IMG_LoadTexture(renderer, "./images/coin_1.png");
		piece[1] = IMG_LoadTexture(renderer, "./images/coin_2.png");
		piece[2] = IMG_LoadTexture(renderer, "./images/coin_3.png");
		piece[3] = IMG_LoadTexture(renderer, "./images/coin_4.png");

		//1:N ; 2:S ; 4:E ; 8:O
		mur = (SDL_Texture **) malloc(sizeof(SDL_Texture*) * 15);
		mur[0] = IMG_LoadTexture(renderer, "./images/Murs_laby/N.png");
		mur[1] = IMG_LoadTexture(renderer, "./images/Murs_laby/S.png");
		mur[2] = IMG_LoadTexture(renderer, "./images/Murs_laby/NS.png");
		mur[3] = IMG_LoadTexture(renderer, "./images/Murs_laby/E.png");
		mur[4] = IMG_LoadTexture(renderer, "./images/Murs_laby/NE.png");
		mur[5] = IMG_LoadTexture(renderer, "./images/Murs_laby/SE.png");
		mur[6] = IMG_LoadTexture(renderer, "./images/Murs_laby/NSE.png");
		mur[7] = IMG_LoadTexture(renderer, "./images/Murs_laby/O.png");
		mur[8] = IMG_LoadTexture(renderer, "./images/Murs_laby/NO.png");
		mur[9] = IMG_LoadTexture(renderer, "./images/Murs_laby/SO.png");
		mur[10] = IMG_LoadTexture(renderer, "./images/Murs_laby/NSO.png");
		mur[11] = IMG_LoadTexture(renderer, "./images/Murs_laby/E0.png");
		mur[12] = IMG_LoadTexture(renderer, "./images/Murs_laby/NEO.png");
		mur[13] = IMG_LoadTexture(renderer, "./images/Murs_laby/SEO.png");
		mur[14] = IMG_LoadTexture(renderer, "./images/Murs_laby/NSEO.png");


		texture_joueur = joueur_D;

		/*
		position_voiture = 0;
		depart = position_voiture;

		cour = cour_chemin;
		
		destination_rect.w = 1080/M;
		destination_rect.h = 720/N;

		origine_rect.w = 1080/M;
		origine_rect.h = 720/N;
		*/
		//Boucle d'evenements
		while (!quit){
			while(!quit && SDL_PollEvent(&event)){
				switch (event.type) {
					case SDL_QUIT: 
						quit = 1;
						break;
					case SDL_KEYDOWN:
						switch(event.key.keysym.sym){
							case SDLK_UP:
								abouge = deplacer_joueur(&position_joueur, 1, labyrinthe.matrice_voisins[position_joueur].direction, M);
								break;
							case SDLK_DOWN:
								abouge = deplacer_joueur(&position_joueur, 2, labyrinthe.matrice_voisins[position_joueur].direction, M);
								break;
							case SDLK_RIGHT:
								abouge = deplacer_joueur(&position_joueur, 4, labyrinthe.matrice_voisins[position_joueur].direction, M);
								texture_joueur = joueur_D;
								break;
							case SDLK_LEFT:
								abouge = deplacer_joueur(&position_joueur, 8, labyrinthe.matrice_voisins[position_joueur].direction, M);
								texture_joueur = joueur_G;
								break;
							case SDLK_ESCAPE:
								quit = 1;
								break;
						}
				}
			}

			//Affichage du labyrinthe
			afficher_texture_labyrinthe(window, mur ,renderer, labyrinthe);
			
			afficher_joueur(position_joueur, N, M, texture_joueur[state], renderer, window);

			if (abouge) {
				//deplacer_ennemi
				abouge=0;
			}
			//afficher_ennemi
			
			if (position_joueur==position_piece) {
				position_piece=rand()%(N*M);
			}

			afficher_piece(position_piece, N, M, piece[state], renderer, window);

			state=(state+1)%4;

			SDL_RenderPresent(renderer);
			SDL_Delay(100);
    	}
	}

	liberer_labyrinthe(&labyrinthe);

	SDL_DestroyTexture(bg_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}