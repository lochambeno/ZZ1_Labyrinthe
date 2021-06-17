#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "vaisseau.h"
#include "asteroid.h"

//git checkout -t origin/... 

int main(){

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

	vaisseau = init_vaisseau(window, text_vaisseau);
	asteroid = creer_asteroid(200, 25);

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

		if(!pause) deplacer_ast(&asteroid, 1, 720);

		afficher_fond(text_fond, window, renderer);
		afficher_ast(text_asteroid, &asteroid, renderer);

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
		
		SDL_RenderPresent(renderer);

		if(SDL_HasIntersection(&(vaisseau.r_collision), &asteroid) && !pause){
			pause = !pause;
		}
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