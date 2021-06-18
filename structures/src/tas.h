#ifndef ZZ1_PROJET_TAS_H
#define ZZ1_PROJET_TAS_H

typedef int data_t;
typedef struct tas_c{
	data_t * tas;
	int nbr_elements; 
}tas_t;

void init_tas(int , tas_t *);
void liberer_tas(tas_t *);

int parent(int fils);
int enfant_G(int parent);
int enfant_D(int parent);

void echange(data_t * a, data_t * b);
void inserer_tas(tas_t * tas, int valeur);

#endif
