#ifndef PARCOURS_H
#define PARCOURS_H
#include "labyrinthe.h"

typedef struct exploration_c {
    int* liste;
    int taille;
} exploration_t;

int* liste_voisins(laby_t, int, int*);
void explorer(laby_t, int**, int, exploration_t*);
exploration_t parcours_prof(laby_t);

#endif 