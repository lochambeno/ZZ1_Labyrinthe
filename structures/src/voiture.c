#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void afficher_voiture(int case_voiture, int direction, int hauteur, int largeur, SDL_Texture ** table_sprite, SDL_Renderer * renderer, SDL_Window * window){
	int win_w, win_h;
	SDL_Rect voiture, source = {0};

	SDL_GetWindowSize(window, &win_w, &win_h);
	voiture.x = (win_w/largeur) * (case_voiture % largeur);
	voiture.y = (win_h/hauteur) * (case_voiture / largeur);

	switch (direction)
	{
	case 1:
		voiture.h = (win_h/hauteur);
		voiture.w = (win_w/largeur)/2;

		SDL_QueryTexture(table_sprite[2], NULL, NULL, &source.w, &source.h);
		SDL_RenderCopy(renderer, table_sprite[2], &source, &voiture);
		break;
	
	case 2:
		voiture.h = (win_h/hauteur);
		voiture.w = (win_w/largeur)/2;

		SDL_QueryTexture(table_sprite[3], NULL, NULL, &source.w, &source.h);
		SDL_RenderCopy(renderer, table_sprite[3], &source, &voiture);
		break;

	case 4:
		voiture.h = (win_h/hauteur)/2;
		voiture.w = (win_w/largeur);

		SDL_QueryTexture(table_sprite[0], NULL, NULL, &source.w, &source.h);
		SDL_RenderCopy(renderer, table_sprite[0], &source, &voiture);
		break;

	case 8:
		voiture.h = (win_h/hauteur)/2;
		voiture.w = (win_w/largeur);

		SDL_QueryTexture(table_sprite[1], NULL, NULL, &source.w, &source.h);
		SDL_RenderCopy(renderer, table_sprite[1], &source, &voiture);
		break;

	default:
		break;
	}
}


/*	
	int temp;

	switch (direction)
	{
	case 1:
		temp = voiture->h;
		voiture->h = voiture->w;
		voiture->w = temp;	

		voiture->y -= 3;

		SDL_RenderCopy(renderer, table_sprite[2], &(taille_sprite[1]), &voiture);
		break;
	
	case 2:
		temp = voiture->h;
		voiture->h = voiture->w;
		voiture->w = temp;	

		voiture->y += 3;

		SDL_RenderCopy(renderer, table_sprite[2], &(taille_sprite[1]), &voiture);
		break;

	case 4:
		temp = voiture->h;
		voiture->h = voiture->w;
		voiture->w = temp;	

		voiture->x += 3;

		SDL_RenderCopy(renderer, table_sprite[2], &(taille_sprite[1]), &voiture);
		break;

	case 8:
		temp = voiture->h;
		voiture->h = voiture->w;
		voiture->w = temp;	

		voiture->x -= 3;

		SDL_RenderCopy(renderer, table_sprite[2], &(taille_sprite[1]), &voiture);
		break;

	default:
		break;
	}
*/