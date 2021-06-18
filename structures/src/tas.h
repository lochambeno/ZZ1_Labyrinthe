#ifndef ZZ1_PROJET_TAS_H
#define ZZ1_PROJEt_TAS_H

typedef int data_t;
typedef struct tas_c{
	data_t * tas;
	int nbr_elements; 
}tas_t;

void init_tas(int , tas_t *);
void liberer_tas(tas_t *);

#endif
