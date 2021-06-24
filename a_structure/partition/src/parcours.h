#ifndef PARCOURS_H
#define PARCOURS_H
#include "labyrinthe.h"

int* liste_voisins(laby_t, int, int*);
void explorer(laby_t, int**, int, int**, int*);
int* parcours_prof(laby_t);

#endif 