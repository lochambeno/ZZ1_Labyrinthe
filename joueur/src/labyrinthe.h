#ifndef ZZ1_PROJET_LABYRINTHE_H
#define ZZ1_PROJET_LABYRINTHE_H

#include "graphe.h"
#include "tas_noeuds.h"

typedef struct case_c{
	int poids;
	int direction;
}case_t;

typedef struct labyrinthe_c{
	graphe_t graph_lab;
	case_t * matrice_voisins;
	int hauteur;
	int largeur;
}labyrinthe_t;

labyrinthe_t init_labyrinthe(int hauteur, int largeur);
void afficher_labyrinthe_NB(SDL_Window * , SDL_Renderer * , labyrinthe_t);
void afficher_texture_labyrinthe(SDL_Window * , SDL_Texture ** , SDL_Renderer * , labyrinthe_t );
void liberer_labyrinthe(labyrinthe_t * labyrinthe);

int direction_labyrinthe(int i, int j, int largeur);
noeud_t * dijkstra(labyrinthe_t labyrinthe, int depart);
void ecrire_chemin_court(noeud_t * table_noeud, int depart, int destination);
liste_t * liste_chemin_court(noeud_t * table_noeud, int depart, int destination);
noeud_t * a_star(labyrinthe_t labyrinthe, int depart, int arrive, int type);

#endif