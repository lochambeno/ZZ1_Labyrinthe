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
				** table_ennemi2_G = NULL,
				** table_ennemi2_D = NULL,
				** table_ennemi3_G = NULL,
				** table_ennemi3_D = NULL,
                ** joueur_D = NULL,
				** joueur_G = NULL,
				** texture_joueur = NULL,
				** piece = NULL,
				** mur = NULL;



	SDL_Color color_text = {255, 255, 255, 100};
    SDL_Rect pos_text = {20, 20, 0, 0}, pos_score = {20, 20, 0, 0};






   TTF_Font* font = NULL;

	SDL_Event event;

	labyrinthe_t labyrinthe = init_labyrinthe(N, M);
	int pause=0, score=0, over=0, quit = 0, abouge=0,
		position_joueur_avant = M*(N-1), position_joueur, direction_joueur,
		position_piece=rand()%(N*M), state=0,
		position_aleatoire,
		position_ennemi = N*M-1, direction_ennemi = 1, orientation_ennemi = 1,
		position_ennemi2 = M-1, direction_ennemi2 = 1, orientation_ennemi2 = 1,
		position_ennemi3 = 0, direction_ennemi3 = 1, orientation_ennemi3 = 1;
		

	position_joueur=position_joueur_avant;
	position_aleatoire=position_ennemi3;
	noeud_t * table_noeud = NULL,
			* table_noeud2 = NULL,
			* table_noeud3 = NULL;
	liste_t * cour_chemin = creer_liste(),
			* cour_chemin2 = creer_liste(),
			* cour_chemin3 = creer_liste();
	liste_t * cour = NULL,
			* cour2 = NULL,
			* cour3 = NULL;



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
			font = TTF_OpenFont("./images/Code.ttf", 65);
		

			


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


			table_ennemi2_D = (SDL_Texture **) malloc(sizeof(SDL_Texture*) * 4);
			table_ennemi2_G = (SDL_Texture **) malloc(sizeof(SDL_Texture*) * 4);

			table_ennemi2_G[0] = IMG_LoadTexture(renderer, "./images/Skeleton2G_1.png");
			table_ennemi2_G[1] = IMG_LoadTexture(renderer, "./images/Skeleton2G_2.png");
			table_ennemi2_G[2] = IMG_LoadTexture(renderer, "./images/Skeleton2G_3.png");
			table_ennemi2_G[3] = IMG_LoadTexture(renderer, "./images/Skeleton2G_4.png");


			table_ennemi2_D[0] = IMG_LoadTexture(renderer, "./images/Skeleton2D_1.png");
			table_ennemi2_D[1] = IMG_LoadTexture(renderer, "./images/Skeleton2D_2.png");
			table_ennemi2_D[2] = IMG_LoadTexture(renderer, "./images/Skeleton2D_3.png");
			table_ennemi2_D[3] = IMG_LoadTexture(renderer, "./images/Skeleton2D_4.png");


			table_ennemi3_D = (SDL_Texture **) malloc(sizeof(SDL_Texture*) * 4);
			table_ennemi3_G = (SDL_Texture **) malloc(sizeof(SDL_Texture*) * 4);

			table_ennemi3_G[0] = IMG_LoadTexture(renderer, "./images/VampireG_1.png");
			table_ennemi3_G[1] = IMG_LoadTexture(renderer, "./images/VampireG_2.png");
			table_ennemi3_G[2] = IMG_LoadTexture(renderer, "./images/VampireG_3.png");
			table_ennemi3_G[3] = IMG_LoadTexture(renderer, "./images/VampireG_4.png");


			table_ennemi3_D[0] = IMG_LoadTexture(renderer, "./images/VampireD_1.png");
			table_ennemi3_D[1] = IMG_LoadTexture(renderer, "./images/VampireD_2.png");
			table_ennemi3_D[2] = IMG_LoadTexture(renderer, "./images/VampireD_3.png");
			table_ennemi3_D[3] = IMG_LoadTexture(renderer, "./images/VampireD_4.png");


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
			cour2 = cour_chemin2;
			cour3 = cour_chemin3;


			while (!quit){
				while(!quit && SDL_PollEvent(&event)){
					switch (event.type) {
						case SDL_QUIT: 
							quit = 1;
							break;
						case SDL_KEYDOWN:
							switch(event.key.keysym.sym){
								case SDLK_UP:
									direction_joueur = 1;
									break;
								case SDLK_DOWN:
									direction_joueur = 2;
									break;
								case SDLK_RIGHT:
									direction_joueur = 4;
									texture_joueur = joueur_D;
									break;
								case SDLK_LEFT:
									direction_joueur = 8;
									texture_joueur = joueur_G;
									break;
								case SDLK_ESCAPE:
									quit = 1;
									break;
								case SDLK_r:
									liberer_liste(&cour_chemin);
									cour_chemin = creer_liste();
									liberer_liste(&cour_chemin2);
									cour_chemin2 = creer_liste();
									liberer_liste(&cour_chemin3);
									cour_chemin3 = creer_liste();
									liberer_labyrinthe(&labyrinthe);
									labyrinthe = init_labyrinthe(N, M);
									score=0;
									over=0;
									pause=0;
									position_joueur_avant = M*(N-1);
									position_joueur=position_joueur_avant;
									position_ennemi = N*M-1;
									position_ennemi2 = M-1;
									position_ennemi3 = 0;
									abouge=0;
									position_piece=rand()%(N*M);
									position_aleatoire=position_ennemi3;
									direction_ennemi = 1;
									orientation_ennemi = 1;
									direction_ennemi2 = 1;
									orientation_ennemi2 = 1;
									direction_ennemi3 = 1;
									orientation_ennemi3 = 1;
									state=0;
									break;
							}
					}
				}

				//Affichage du labyrinthe
				afficher_texture_labyrinthe(window, mur ,renderer, labyrinthe);

				if (!pause && direction_joueur) {
					abouge+=deplacer_joueur(&position_joueur, direction_joueur, labyrinthe.matrice_voisins[position_joueur].direction, M);
					direction_joueur = 0;
				}

				if (!pause && abouge==2 && position_ennemi != position_joueur && position_ennemi2 != position_joueur && position_ennemi3 != position_joueur) 
				{
					table_noeud = dijkstra(labyrinthe, position_ennemi);
					cour_chemin = liste_chemin_court(table_noeud, position_ennemi, position_joueur);
					cour = cour_chemin;
					direction_ennemi = direction_labyrinthe(position_ennemi, cour->val, M);
					position_ennemi = cour->val;
					cour = cour->suiv;
					liberer_liste(&cour_chemin);
					free(table_noeud);

					table_noeud2 = dijkstra(labyrinthe, position_ennemi2);
					cour_chemin2 = liste_chemin_court(table_noeud2, position_ennemi2, position_joueur_avant);
					cour2 = cour_chemin2;
					direction_ennemi2 = direction_labyrinthe(position_ennemi2, cour2->val, M);
					position_ennemi2 = cour2->val;
					cour2 = cour2->suiv;
					liberer_liste(&cour_chemin2);
					free(table_noeud2);

					if (cour3 != NULL && position_ennemi3!=position_aleatoire) {
						direction_ennemi3 = direction_labyrinthe(position_ennemi3, cour3->val, M);
						position_ennemi3 = cour3->val;
						cour3 = cour3->suiv;
					}
					else {
						liberer_liste(&cour_chemin3);
						free(table_noeud3);
						
						position_aleatoire=rand()%(N*M);
						table_noeud3 = dijkstra(labyrinthe, position_ennemi3);
						cour_chemin3 = liste_chemin_court(table_noeud3, position_ennemi3, position_aleatoire);
						cour3 = cour_chemin3;
					}
					abouge=0;
				}

				afficher_joueur(position_joueur, N, M, texture_joueur[state], renderer, window);

				afficher_ennemi(position_ennemi, N, M, direction_ennemi, table_ennemi_D, table_ennemi_G, state, &orientation_ennemi, renderer, window);
				afficher_ennemi(position_ennemi2, N, M, direction_ennemi2, table_ennemi2_D, table_ennemi2_G, state, &orientation_ennemi2, renderer, window);
				afficher_ennemi(position_ennemi3, N, M, direction_ennemi3, table_ennemi3_D, table_ennemi3_G, state, &orientation_ennemi3, renderer, window);

				if (position_joueur==position_piece) {
					position_piece=rand()%(N*M);
					score+=1;
				}

				if (position_ennemi3==position_aleatoire) {
						liberer_liste(&cour_chemin3);
						free(table_noeud3);
						
						position_aleatoire=rand()%(N*M);
						table_noeud3 = dijkstra(labyrinthe, position_ennemi3);
						cour_chemin3 = liste_chemin_court(table_noeud3, position_ennemi3, position_aleatoire);
						cour3 = cour_chemin3;
				}

				if(!pause && (position_ennemi == position_joueur || position_ennemi2 == position_joueur || position_ennemi3 == position_joueur))
				{
					over=!over;
					pause=!pause;
				}

				afficher_piece(position_piece, N, M, piece[state], renderer, window);
				afficher_score(renderer, font, color_text, pos_text, pos_score, score);
				
				if (over) 
				{
					SDL_Color color_text = {255, 255, 255, 255};
					afficher_score(renderer, font, color_text, pos_text, pos_score, score);
					game_over(window, renderer, font, color_text);
				}

				state=(state+1)%4;
				position_joueur_avant=position_joueur;
		

				SDL_RenderPresent(renderer);
				SDL_Delay(100);
			}
		}
	}

	liberer_liste(&cour_chemin);
	liberer_liste(&cour_chemin3);
	liberer_labyrinthe(&labyrinthe);

	SDL_DestroyTexture(bg_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}