#ifndef ZZ1_PROJET_PARTITION_H
#define ZZ1_PROJET_PARTITION_H

#include "liste.h"

//typedef int data_p;

typedef struct partition_c{
	int taille;
	int * parent;
	int * hauteur;
}partition_t;

partition_t init_partition(int);
int classe_element_partition(int, partition_t);
void fusion_partition(int, int, partition_t*);

liste_t * liste_el_classe_partition(int, partition_t);
liste_t ** liste_classes_partition(partition_t);

void creer_affichage_partition(partition_t );

void liberer_partition(partition_t *);
void liberer_table_partition(liste_t ***, int);
void afficher_table_partition(liste_t **, int);

#endif