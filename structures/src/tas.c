#include <stdio.h>
#include "tas.h"

void init_tas(int taille, tas_t * a_init){
	a_init->tas = (data_t *) malloc(sizeof(data_t)*taille);
	a_init->nbr_elements = 0;

	if(a_init->tas == NULL){
		a_init = NULL;
	}
}

void liberer_tas(tas_t * a_liberer){
	free(a_liberer->tas);
}

int parent(int fils){
	return fils/2;
}

int enfant_G(int parent){
	return 2*parent;
}

int enfant_D(int parent){
	return 2*parent + 1;
}

void trier_element_tas(tas_t * tas, int i){
	
}

void inserer_tas(tas_t * tas){

}

