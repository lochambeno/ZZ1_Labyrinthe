#ifndef LABYRINTHE_H
#define LABYRINTHE_H
#include "partition.h"
#include "connexe.h"
#include "kruskal.h"

typedef struct carac_c {
    int NSEO;
    int poids;
} carac_t;

typedef struct laby_c {
    graphe_t graphe;
    int hauteur;    
    int largeur;
    carac_t* caracteristique;
} laby_t;

laby_t init_laby(int, int);
void init_carac_laby(laby_t*);
void afficher_carac(laby_t);
void liberer_labyrinthe(laby_t*);
laby_t creer_laby(int, int);

#endif