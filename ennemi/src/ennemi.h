#ifndef ZZ1_PROJET_ENNEMI_H
#define ZZ1_PROJET_ENNEMI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void afficher_ennemi(int case_ennemi, int hauteur, int largeur, int direction, SDL_Texture ** table_ennemi_D, SDL_Texture ** table_ennemi_G, int state, int* orientation_ennemi, SDL_Renderer * renderer, SDL_Window * window);

#endif