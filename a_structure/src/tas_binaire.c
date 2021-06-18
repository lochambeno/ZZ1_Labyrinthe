#include <stdio.h>
#include <stdlib.h>
#include "tas_binaire.h"

void init_tas(int taille, tas_t* p_tas) {
    p_tas->nbr_elements = 0;
    p_tas->tas=(data_t*)malloc(taille*sizeof(data_t));

    if (p_tas->tas == NULL) p_tas = NULL;
}

void liberer_tas(tas_t* p_tas) {
    free(p_tas->tas);
}

int parent(int enfant) {
    return (enfant-1)/2;
}

int enfant_gauche(int parent) {
    return 2*parent+1;
}

int enfant_droite(int parent) {
    return 2*parent+2;
}

void echange_tas(tas_t* p_tas, int i, int j) {
    data_t temp = p_tas->tas[i];
    p_tas->tas[i] = p_tas->tas[j];
    p_tas->tas[j] = temp;
}

void inserer_tas(tas_t* p_tas, data_t value) {
    int i = p_tas->nbr_elements;
    p_tas->tas[i] = value;
    while (p_tas->tas[parent(i)]>value) {
        echange_tas(p_tas, i, parent(i));
        i=parent(i);
    }
    ++(p_tas->nbr_elements);
}

int min_enfant(tas_t tas, int i) {
    int j=enfant_droite(i);
    if (tas.tas[enfant_gauche(i)] <= tas.tas[enfant_droite(i)]) j=enfant_gauche(i);
    return j;
}

void supprimer_tas(tas_t* p_tas, int i) {
    --(p_tas->nbr_elements);
    int nbr_elements = p_tas->nbr_elements, j, fin=0;
    p_tas->tas[i]=p_tas->tas[nbr_elements];

    do {
        j=enfant_gauche(i);
        if (j <= nbr_elements) {
            if (enfant_droite(i) <= nbr_elements) {
                j=min_enfant(*p_tas, i);
                if (p_tas->tas[i] > p_tas->tas[j]) {
                    echange_tas(p_tas, i, j);
                    i=j;
                }
            }
            else {
                if (p_tas->tas[i] > p_tas->tas[j]) {
                    echange_tas(p_tas, i, j);
                }
                fin=1;
            }
        }
        else fin=1;
    } while (!fin);
}

void afficher_tas(tas_t tas) {
    int i = 0;
    for (i=0;i<tas.nbr_elements;++i) {
        printf("%d ", tas.tas[i]);
    }
    printf("\n");
}