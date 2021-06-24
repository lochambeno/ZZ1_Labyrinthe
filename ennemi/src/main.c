#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "tas_noeuds.h"
#include "partition.h"
#include "liste.h"
#include "graphe.h"
#include "labyrinthe.h"
#include "ennemi.h"
#include "joueur.h"
#include "piece.h"
#include "score.h"

#define N 10
#define M 15

int main(){	
	srand(time(NULL));
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL; 
	SDL_Texture * bg_texture = NULL;
	SDL_Texture ** table_ennemi_G = NULL,
                ** table_ennemi_D = NULL,
                ** joueur_D = NULL,
				** joueur_G = NULL,
				** texture_joueur = NULL,
				** piece = NULL,
				** mur = NULL;



	SDL_Color color_text = {255, 255, 255, 255};
    SDL_Rect pos_text = {20, 20, 0, 0}, pos_score = {20, 20, 0, 0};






   TTF_Font* font = NULL;

	SDL_Event event;

	labyrinthe_t labyrinthe = init_labyrinthe(N, M);
	int score=0, over=0, quit = 0, position_joueur = 0, position_ennemi=N*M-1,abouge=0,position_piece=rand()%(N*M), direction_ennemi = 1, orientation_ennemi = 1, state=0, state_e=0;
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

		if (TTF_Init() == 0) {
			font = TTF_OpenFont("./images/SubZER0.ttf", 65);
		

			bg_texture = IMG_LoadTexture(renderer, "./images/roadTextures_tilesheet@2.png");
			if(bg_texture == NULL){
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				SDL_Quit();
				exit(EXIT_FAILURE);
			}


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

			texture_joueur = joueur_D;
		

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


			cour = cour_chemin;


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



				if (abouge && position_ennemi != position_joueur) 
				{
					table_noeud = dijkstra(labyrinthe, position_ennemi);

					cour_chemin = liste_chemin_court(table_noeud, position_ennemi, position_joueur);
						
					cour = cour_chemin; 

					direction_ennemi = direction_labyrinthe(position_ennemi, cour->val, M);

					position_ennemi = cour->val;
					cour = cour->suiv;

					liberer_liste(&cour_chemin);
					free(table_noeud);

					abouge=0;
				}
				afficher_ennemi(position_ennemi, N, M, direction_ennemi, table_ennemi_D, table_ennemi_G,state_e, &orientation_ennemi, renderer, window);

				if (position_joueur==position_piece) {
					position_piece=rand()%(N*M);
					score+=1;
				}

				if(position_ennemi == position_joueur)
				{
					over=!over;
				}

				afficher_piece(position_piece, N, M, piece[state], renderer, window);
				afficher_score(renderer, font, color_text, pos_text, pos_score, score);
				
				if (over) 
				{
				game_over(window, renderer, font, color_text);
				}

				state=(state+1)%4;
				state_e=(state_e+1)%4;

		

				SDL_RenderPresent(renderer);
				SDL_Delay(100);
			}
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