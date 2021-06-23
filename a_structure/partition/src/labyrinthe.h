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

#endif