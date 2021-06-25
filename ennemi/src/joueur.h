#ifndef ZZ1_PROJET_JOUEUR_H
#define ZZ1_PROJET_JOUEUR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void afficher_joueur(int case_joueur, int hauteur, int largeur, SDL_Texture * texture_joueur, SDL_Renderer * renderer, SDL_Window * window);
int deplacer_joueur(int* case_joueur, int direction, int voisin, int largeur);

#endif 