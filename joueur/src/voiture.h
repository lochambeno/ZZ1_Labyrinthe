#ifndef ZZ1_PROJET_VOITURE_H
#define ZZ1_PROJET_VOITURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void afficher_voiture(int case_voiture, int direction, int hauteur, int largeur, SDL_Texture ** table_sprite, SDL_Renderer * renderer, SDL_Window * window);
#endif