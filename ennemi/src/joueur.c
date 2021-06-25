#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "joueur.h"

void afficher_joueur(int case_joueur, int hauteur, int largeur, SDL_Texture * texture_joueur, SDL_Renderer * renderer, SDL_Window * window) {
    int win_w, win_h;
    float zoom = 0.5;
	SDL_Rect joueur, source = {0};

	SDL_GetWindowSize(window, &win_w, &win_h);
	joueur.x = (1-zoom)*(win_w/largeur)/2 + (win_w/largeur) * (case_joueur % largeur);
	joueur.y = (1-zoom)*(win_h/hauteur)/2 + (win_h/hauteur) * (case_joueur / largeur);
    joueur.w = zoom * (win_w/largeur);
    joueur.h = zoom * (win_h/hauteur);

    SDL_QueryTexture(texture_joueur, NULL, NULL, &source.w, &source.h);
	SDL_RenderCopy(renderer, texture_joueur, &source, &joueur);
}

int deplacer_joueur(int* case_joueur, int direction, int voisin, int largeur) {
    int succes = 0;
    if (direction & voisin) {
        switch (direction) {
            case 1:
                *case_joueur-=largeur;
                break;
            case 2:
                *case_joueur+=largeur;
                break;
            case 4:
                ++(*case_joueur);
                break;
            case 8:
                --(*case_joueur);
                break;
        }
        succes = 1;
    }
    return succes;
}