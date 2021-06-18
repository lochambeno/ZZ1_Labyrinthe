#include <stdio.h>
#include <stdlib.h>
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
	return (fils-1)/2;
}

int enfant_G(int parent){
	return 2*parent + 1;
}

int enfant_D(int parent){
	return 2*parent + 2;
}

void echange(data_t * a, data_t * b){
	int c = *a;
	*a = *b;
	*b = c;
}

void inserer_tas(tas_t * tas, int valeur){
	int i = tas->nbr_elements;
		tas->tas[i] = valeur;
	
	while(tas->tas[i] < tas->tas[parent(i)]){
		echange(&(tas->tas[i]), &(tas->tas[parent(i)]));
		i = parent(i);
	}
	tas->nbr_elements += 1;
}

//se fait avec 
void supprimer_tas(tas_t * tas, int a_supprime){
	//idee on ecrase l'element a supprimer avec l'element en fin
	//puis on fait descendre l'element en l'echangeant avec son 
	//fils le plus petit (et inferieur a lui)

	
}

