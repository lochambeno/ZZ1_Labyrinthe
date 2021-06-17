#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "window.h"
#include "score.h"

int main1() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;
    TTF_Font* font = NULL;

    /* Initialisation de la SDL */
    create_sdl(&window, &renderer, &screen, &font, "chef_d_oeuvre", "./SubZER0.ttf", 1, 1);
    
    /* Variables du programme */
    SDL_Color color_text = {255, 255, 255, 255};
    SDL_Rect pos_text = {20, 20, 0, 0}, pos_score = {20, 20, 0, 0};
    int score=0;

    /* Boucle des événements */
    SDL_bool
        program_on = SDL_TRUE,
        paused = SDL_FALSE,
        over = SDL_FALSE;
    while (program_on) {
        SDL_Event event;

        while (program_on && SDL_PollEvent(&event)) {
                                                        
            switch (event.type) {
            case SDL_QUIT:
                program_on = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
                                                        
                switch (event.key.keysym.sym) {
                case SDLK_p:
                case SDLK_SPACE:
                    paused = !paused;
                    break;
                case SDLK_ESCAPE:
                case SDLK_q:
                    program_on = 0;
                    break;
                case SDLK_k:
                    paused = !paused;
                    over = SDL_TRUE;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
        
        afficher_score(window, renderer, font, color_text, pos_text, pos_score, score);

        if (!paused) {
        
            score+=10;
        }
        if (over) {
            game_over(window, renderer, screen, font, color_text);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    /* Fermeture de la SDL */
    end_sdl(1, "Normal ending", window, renderer);

    return 0;
#include "vaisseau.h"
#include "asteroid.h"
#include <stdlib.h>
#include <time.h>

#define NBR_ASTEROIDS 40
//git checkout -t origin/... 

SDL_Rect tab_init_ast[NBR_ASTEROIDS];


int main3(){

  	srand(time(NULL));

	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
	SDL_Texture * text_vaisseau = NULL,
				* text_vaisseauD = NULL,
				* text_vaisseauG = NULL,
				* text_fond = NULL,
				* text_asteroid = NULL;

	SDL_Rect 	fond,
				asteroid;

	vaisseau_t vaisseau;

	int fin_programme = 0,
		pause = 0,
		texture = 0;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    	SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); 
    	exit(EXIT_FAILURE);
  	}

	window = SDL_CreateWindow(
		"Jeu",
		SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
		1080,
        720,
		0);

	if(window == NULL){
		SDL_Log("Error : window initialisation - %s\n", SDL_GetError()); 
		SDL_Quit();
    	exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == NULL){
		SDL_DestroyWindow(window);
		SDL_Quit();
		SDL_Log("Error : window initialisation - %s\n", SDL_GetError()); 
    	exit(EXIT_FAILURE);
	}

	text_vaisseau = IMG_LoadTexture(renderer, "./images/redfighter5.png");
	if (text_vaisseau == NULL){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		SDL_Log("Error : window initialisation - %s\n", SDL_GetError()); 
    	exit(EXIT_FAILURE);
	}

	text_vaisseauG = IMG_LoadTexture(renderer, "./images/redfighter1.png");
	if (text_vaisseau == NULL){
		SDL_DestroyTexture(text_vaisseau);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		SDL_Log("Error : window initialisation - %s\n", SDL_GetError()); 
    	exit(EXIT_FAILURE);
	}

	text_vaisseauD = IMG_LoadTexture(renderer, "./images/redfighter9.png");
	if (text_vaisseau == NULL){
		SDL_DestroyTexture(text_vaisseauG);
		SDL_DestroyTexture(text_vaisseau);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		SDL_Log("Error : window initialisation - %s\n", SDL_GetError()); 
    	exit(EXIT_FAILURE);
	}

	text_fond = IMG_LoadTexture(renderer, "./images/Space01.png");
	if (text_vaisseau == NULL){
		SDL_DestroyTexture(text_vaisseauD);
		SDL_DestroyTexture(text_vaisseauG);
		SDL_DestroyTexture(text_vaisseau);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		SDL_Log("Error : window initialisation - %s\n", SDL_GetError()); 
    	exit(EXIT_FAILURE);
	}

	text_asteroid = IMG_LoadTexture(renderer, "./images/Asteroids.png");
	if (text_vaisseau == NULL){
		SDL_DestroyTexture(text_fond);
		SDL_DestroyTexture(text_vaisseauD);
		SDL_DestroyTexture(text_vaisseauG);
		SDL_DestroyTexture(text_vaisseau);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		SDL_Log("Error : window initialisation - %s\n", SDL_GetError()); 
    	exit(EXIT_FAILURE);
	}
	init_ast(1080);
	vaisseau = init_vaisseau(window, text_vaisseau);

	while (!fin_programme){
        SDL_Event event;
            while(!fin_programme && SDL_PollEvent(&event)){
                switch(event.type){
                case SDL_QUIT:
                    fin_programme = 1;
                    break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
					case SDLK_RIGHT:
						if(!pause){
							bouger_vaisseau_D(&vaisseau, 1080);
							texture = 1;
						}
						break;
					case SDLK_LEFT:
						if(!pause){ 
							bouger_vaisseau_G(&vaisseau);
							texture = 2;
						}
						break;
                    default:
                           break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                            
                default:
					texture = 0;
                    break;
                }
            }

		//gestion des textures
		afficher_fond(text_fond, window, renderer);

		if(!pause) {
			for(int i=0; i<NBR_ASTEROIDS; i++){
				deplacer_ast(&tab_init_ast[i], 3, 720);
				afficher_ast(text_asteroid, tab_init_ast[i], renderer);
			}
		}

		if(texture == 1){
			afficher_vaisseau(vaisseau, text_vaisseauD, renderer);
		}
		else
			if(texture == 2){
				afficher_vaisseau(vaisseau, text_vaisseauG, renderer);
			}
			else { 
				afficher_vaisseau(vaisseau, text_vaisseau, renderer);
			}
		
		//affichage des textures
		SDL_RenderPresent(renderer);

		//si on a une collision, on met en pause
		if(SDL_HasIntersection(&(vaisseau.r_collision), &asteroid) && !pause){
			pause = !pause;
		}
	SDL_Delay(10);
    }

	SDL_DestroyTexture(text_asteroid);
	SDL_DestroyTexture(text_fond);
	SDL_DestroyTexture(text_vaisseauD);
	SDL_DestroyTexture(text_vaisseauG);
	SDL_DestroyTexture(text_vaisseau);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window); 
	IMG_Quit();
	SDL_Quit();
}