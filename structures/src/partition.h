#ifndef ZZ1_PROJET_PARTITION_H
#define ZZ1_PROJET_PARTITION_H

//typedef int data_p;

typedef struct partition_c{
	int taille;
	int * parent;
	int * hauteur;
}partition_t;

partition_t init_partition(int);
int classe_element_partition(int, partition_t);
void fusion_partition(int, int, partition_t*);

int * liste_classes_partition(int, partition_t);
int * liste_el_classes_partition(int, partition_t);

void creer_affichage_partition(partition_t partition);

#endif