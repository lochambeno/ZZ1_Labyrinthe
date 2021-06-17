#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define VITESSE 3

//(x+max)%max+1

//bouge le vaisseau selon la touche pressee
void bouger_vaisseau_G(SDL_Rect * vaisseau){
	if((*vaisseau).x - VITESSE <= 0)
		(*vaisseau).x = 0;
	else
		(*vaisseau).x -= VITESSE;
}

void bouger_vaisseau_D(SDL_Rect * vaisseau, int largeur_fenetre){
	if((*vaisseau).x + VITESSE <= largeur_fenetre)
		(*vaisseau).x = largeur_fenetre-1;
	else
		(*vaisseau).x += VITESSE;
}

//actualise l'affichage du vaisseau
void afficher_vaisseau(SDL_Rect * vaisseau, SDL_Texture * text_vaisseau, SDL_Renderer * renderer){
	SDL_Rect source;

	SDL_QueryTexture(text_vaisseau, NULL, NULL, &source.w, &source.h);
	SDL_RenderCopy(renderer, text_vaisseau, &source, &vaisseau);
}

//a supprimer, juste la pour tester
int main(){

	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    	SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); 
    	exit(EXIT_FAILURE);
  	}

	

}

