#ifndef ZZ1_PROJET_TAS_H
#define ZZ1_PROJET_TAS_H

//typedef int data_p;
typedef struct part_c{
	int taille;
    int* parent;
    int* hauteur;
}part_t;

part_t init_part(int);
void afficher_part(part_t);
int recuperer_classe(part_t , int);
void fusion_part(part_t* , int , int);


#endif