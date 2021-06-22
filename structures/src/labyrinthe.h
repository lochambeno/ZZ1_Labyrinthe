#ifndef ZZ1_PROJET_LABYRINTHE_H
#define ZZ1_PROJET_LABYRINTHE_H

#include "graphe.h"

typedef struct labyrinthe_c{
	graphe_t graph_lab;
	int * matrice_voisins;
	int hauteur;
	int largeur;
}labyrinthe_t;

labyrinthe_t init_labyrinthe(int hauteur, int largeur);
void afficher_labyrinthe(SDL_Window * , SDL_Renderer * , labyrinthe_t);

#endif