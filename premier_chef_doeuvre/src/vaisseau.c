#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define VITESSE 20

//(x+max)%max+1 

SDL_Rect init_vaisseau(SDL_Window * window, SDL_Texture * text_vaisseau){
	SDL_DisplayMode screen;
	SDL_Rect 	vaisseau;

	int w_window, h_window, w_vaisseau, h_vaisseau;

	SDL_GetWindowSize(window, &w_window, &h_window);
	SDL_QueryTexture(text_vaisseau, NULL, NULL, &w_vaisseau, &h_vaisseau);
	
	vaisseau.x = (w_window - w_vaisseau/4)/2;
	vaisseau.y = h_window - h_vaisseau/4;
	vaisseau.h = h_vaisseau/4;
	vaisseau.w = w_vaisseau/4;

	return vaisseau;
}

//bouge le vaisseau selon la touche pressee
void bouger_vaisseau_G(SDL_Rect * vaisseau){
	if(vaisseau->x - VITESSE <= 0)
		vaisseau->x = 0;
	else
		vaisseau->x -= VITESSE;
}

void bouger_vaisseau_D(SDL_Rect * vaisseau, int largeur_fenetre){
	if(vaisseau->x + VITESSE + vaisseau->w >= largeur_fenetre){
		vaisseau->x = largeur_fenetre - vaisseau->w;
	}
	else{
		vaisseau->x += VITESSE;
	}
}

//actualise l'affichage du vaisseau 
void afficher_vaisseau(SDL_Rect vaisseau, SDL_Texture * text_vaisseau, SDL_Renderer * renderer){
	SDL_Rect source = {0};

	SDL_QueryTexture(text_vaisseau, NULL, NULL, &source.w, &source.h);
	SDL_RenderCopy(renderer, text_vaisseau, &source, &vaisseau);
}


