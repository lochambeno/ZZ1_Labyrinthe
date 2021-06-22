#ifndef ZZ1_PROJET_PART_H
#define ZZ1_PROJET_PART_H

#include "liste.h"


typedef struct part_c{
	int taille;
    int* parent;
    int* hauteur;
}part_t;

part_t init_part(int);
void afficher_part(part_t);
int recuperer_classe(part_t , int);
void fusion_part(part_t* , int , int);
liste_t* lister_elt(part_t , int);
liste_t** lister_classes(part_t);
void liberer_classes(liste_t ** , int);
void liberer_partition(part_t*);


#endif