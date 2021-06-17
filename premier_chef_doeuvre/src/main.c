#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "window.h"
#include "score.h"
#include "vaisseau.h"
#include "asteroid.h"
#include <stdlib.h>
#include <time.h>

#define NBR_ASTEROIDS 40
//git checkout -t origin/... 

SDL_Rect tab_asteroids[NBR_ASTEROIDS];


/*int main1() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;
    TTF_Font* font = NULL;

     Initialisation de la SDL 
    
    
     Variables du programme 
    

     Boucle des événements 
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
        
        

        
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

     Fermeture de la SDL 
    end_sdl(1, "Normal ending", window, renderer);

    return 0;
#include "vaisseau.h"
#include "asteroid.h"
#include <stdlib.h>
#include <time.h>
*/

int main(){
	srand(time(NULL));

	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
	SDL_Texture * text_vaisseau = NULL,
				* text_vaisseauD = NULL,
				* text_vaisseauG = NULL,
				* text_fond = NULL,
				* text_asteroid = NULL;

	//SDL_DisplayMode screen;
	SDL_Color color_text = {255, 255, 255, 255};
    SDL_Rect pos_text = {20, 20, 0, 0}, pos_score = {20, 20, 0, 0};

    TTF_Font* font = NULL;

	SDL_Rect 	fond,
				asteroid;

	vaisseau_t vaisseau;

	int fin_programme = 0,
		pause = 0,
		texture = 0,
		i,
		score = 0,
		over = 0;

	int deplace_gauche = 0,
		deplace_droite = 0;

	create_sdl(&window, &renderer, &font, "chef_d_oeuvre", "./images/SubZER0.ttf", 1, 1);

	//initialisation des textures
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

	//initialisation des parametres initiaux
	vaisseau = init_vaisseau(window, text_vaisseau);
	
	for(i=0; i<NBR_ASTEROIDS; i++){
		tab_asteroids[i] = creer_asteroid((i*100)%1100, -rand()%2500);
	}

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
						deplace_droite = 1;
						break;
					case SDLK_LEFT:
						deplace_gauche = 1;
						break;
                    default:
                           break;
                    }
                    break;

				case SDL_KEYUP:
					switch(event.key.keysym.sym){
						case SDLK_RIGHT:
							deplace_droite = 0;
							break;

						case SDLK_LEFT:
							deplace_gauche = 0;
							break;

						default:
                           break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                            
                default:
                    break;
                }
            }

		//gestion des textures
		afficher_fond(text_fond, window, renderer);
		
		for(int i=0; i<NBR_ASTEROIDS; i++){
			if(!pause) deplacer_ast(&tab_asteroids[i], 3, 720);
				afficher_ast(text_asteroid, tab_asteroids[i], renderer);
		}

		//gestion du vaisseau
		if(deplace_droite && !pause){
			bouger_vaisseau_D(&vaisseau, 1080);
			afficher_vaisseau(vaisseau, text_vaisseauD, renderer);
		}
		else
			if(deplace_gauche && !pause){
				bouger_vaisseau_G(&vaisseau);
				afficher_vaisseau(vaisseau, text_vaisseauG, renderer);
			}
			else{
				afficher_vaisseau(vaisseau, text_vaisseau, renderer);
			}
		
		//si on a une collision, on met en pause
		for(i=0; i<NBR_ASTEROIDS; i++){
			if(SDL_HasIntersection(&(vaisseau.r_collision), &tab_asteroids[i]) && !pause){
				pause = !pause;
				over = !over;
			}
		}

		afficher_score(window, renderer, font, color_text, pos_text, pos_score, score);
		//affichage des textures

		if (!pause) {
            score+=10;
        }
        if (over) {
            game_over(window, renderer, font, color_text);
        }
		SDL_RenderPresent(renderer);

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