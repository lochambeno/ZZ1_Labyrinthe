#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "vaisseau.h"

#define VITESSE 10

//(x+max)%max+1 

vaisseau_t init_vaisseau(SDL_Window * window, SDL_Texture * text_vaisseau){
	SDL_DisplayMode screen;
	vaisseau_t 	vaisseau;

	int w_window, h_window, w_vaisseau, h_vaisseau;

	SDL_GetWindowSize(window, &w_window, &h_window);
	SDL_QueryTexture(text_vaisseau, NULL, NULL, &w_vaisseau, &h_vaisseau);
	
	vaisseau.r_sprite.x = (w_window - w_vaisseau/4)/2;
	vaisseau.r_sprite.y = h_window - h_vaisseau/4;
	vaisseau.r_sprite.h = h_vaisseau/4;
	vaisseau.r_sprite.w = w_vaisseau/4;

	vaisseau.r_collision.x = vaisseau.r_sprite.x + vaisseau.r_sprite.w/3;
	vaisseau.r_collision.y = vaisseau.r_sprite.y;
	vaisseau.r_collision.h = vaisseau.r_sprite.h;
	vaisseau.r_collision.w = vaisseau.r_sprite.w/3;

	return vaisseau;
}

//bouge le vaisseau selon la touche pressee
void bouger_vaisseau_G(vaisseau_t * vaisseau){
	if(vaisseau->r_sprite.x - VITESSE <= 0){
		vaisseau->r_sprite.x = 0;
		vaisseau->r_collision.x = vaisseau->r_sprite.w/3;
	}
	else{
		vaisseau->r_sprite.x -= VITESSE;
		vaisseau->r_collision.x -= VITESSE;
	}
}

void bouger_vaisseau_D(vaisseau_t * vaisseau, int largeur_fenetre){
	if(vaisseau->r_sprite.x + VITESSE + vaisseau->r_sprite.w >= largeur_fenetre){
		vaisseau->r_sprite.x = largeur_fenetre - vaisseau->r_sprite.w;
		vaisseau->r_collision.x = largeur_fenetre - 2*vaisseau->r_sprite.w/3;
	}
	else{
		vaisseau->r_sprite.x += VITESSE;
		vaisseau->r_collision.x += VITESSE;
	}
}

//actualise l'affichage du vaisseau 
void afficher_vaisseau(vaisseau_t vaisseau, SDL_Texture * text_vaisseau, SDL_Renderer * renderer){
	SDL_Rect source = {0};

	SDL_QueryTexture(text_vaisseau, NULL, NULL, &source.w, &source.h);
	SDL_RenderCopy(renderer, text_vaisseau, &source, &(vaisseau.r_sprite));
}


