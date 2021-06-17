#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "vaisseau.h"

int main(){

	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
	SDL_Texture * text_vaisseau = NULL;

	SDL_Rect vaisseau;

	int fin_programme = 0;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    	SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); 
    	exit(EXIT_FAILURE);
  	}

	window = SDL_CreateWindow(
		"Test_Texture",
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

	

	while (!fin_programme){
        SDL_Event event;
            while(!fin_programme && SDL_PollEvent(&event)){
                    switch(event.type){
                    case SDL_QUIT:
                        fin_programme = 1;
                        break;

                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){

                        default:
                               break;
                        }
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                            
                    default:
                        break;
                    }
              }
              
              afficher_vaisseau(vaisseau, text_vaisseau, renderer);
              SDL_RenderPresent(renderer);
              SDL_Delay(50);
       }


	SDL_Quit();
}