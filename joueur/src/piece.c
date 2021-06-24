#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "piece.h"

void afficher_piece(int case_piece, int hauteur, int largeur, SDL_Texture * texture_piece, SDL_Renderer * renderer, SDL_Window * window) {
    int win_w, win_h;
    float zoom = 0.66;
	SDL_Rect piece, source = {0};

	SDL_GetWindowSize(window, &win_w, &win_h);
	piece.x = (1-zoom)*(win_w/largeur)/2 + (win_w/largeur) * (case_piece % largeur);
	piece.y = (1-zoom)*(win_h/hauteur)/2 + (win_h/hauteur) * (case_piece / largeur);
    piece.w = zoom * (win_w/largeur);
    piece.h = zoom * (win_h/hauteur);

    SDL_QueryTexture(texture_piece, NULL, NULL, &source.w, &source.h);
	SDL_RenderCopy(renderer, texture_piece, &source, &piece);
}