#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>


void afficher_ennemi(int case_ennemi, int hauteur, int largeur, int direction, SDL_Texture ** table_ennemi_D, SDL_Texture ** table_ennemi_G, int state, int* orientation_ennemi, SDL_Renderer * renderer, SDL_Window * window){
	int win_w, win_h;
    float zoom = 0.66;
	SDL_Rect ennemi, source = {0};

	SDL_GetWindowSize(window, &win_w, &win_h);
	ennemi.x = (1-zoom)*(win_w/largeur)/2 + (win_w/largeur) * (case_ennemi % largeur);
	ennemi.y = (1-zoom)*(win_h/hauteur)/2 + (win_h/hauteur) * (case_ennemi / largeur);
    ennemi.h = zoom * (win_h/hauteur);
	ennemi.w = zoom * (win_w/largeur);

    if (direction == 4) *orientation_ennemi=1;
    if (direction == 8) *orientation_ennemi=0;
	

	if (*orientation_ennemi) 
    {
        SDL_QueryTexture(table_ennemi_D[state], NULL, NULL, &source.w, &source.h);
        SDL_RenderCopy(renderer, table_ennemi_D[state], &source, &ennemi);
    }
    else 
    {
        SDL_QueryTexture(table_ennemi_G[state], NULL, NULL, &source.w, &source.h);
        SDL_RenderCopy(renderer, table_ennemi_G[state], &source, &ennemi);
    }
            
	
}