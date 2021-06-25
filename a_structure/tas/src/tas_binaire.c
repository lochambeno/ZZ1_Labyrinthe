#include <stdio.h>
#include <stdlib.h>
#include "tas_binaire.h"
#define TAILLE 5

tas_t init_tas() {
    tas_t tas;
    tas.nbr_elements = 0;
    tas.taille=TAILLE;
    tas.tas=(data_t*)malloc(tas.taille*sizeof(data_t));
    return tas;
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

int inserer_tas(tas_t* p_tas, data_t value) {
    int i = p_tas->nbr_elements;
    int error = 0;
    if (i==p_tas->taille) {
        data_t* temp=NULL;
        p_tas->taille*=1.5;
        temp=(data_t*)realloc(p_tas->tas, (p_tas->taille)*sizeof(data_t));
        if (temp == NULL) error =1;
        else p_tas->tas=temp;    
    }
    p_tas->tas[i] = value;
    while (p_tas->tas[parent(i)]>value) {
        echange_tas(p_tas, i, parent(i));
        i=parent(i);
    }
    ++(p_tas->nbr_elements);
    return error;
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
        if (j <= nbr_elements-1) {
            if (enfant_droite(i) <= nbr_elements-1) {
                j=min_enfant(*p_tas, i);
                if (p_tas->tas[i] > p_tas->tas[j]) {
                    echange_tas(p_tas, i, j);
                    i=j;
                }
                else fin=1;
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

int tri_tas(data_t liste[], int nbr_elements) {
    int i=0, error=0;
    tas_t tas = init_tas();
    if (tas.tas!=NULL) {
        while (!error && i<nbr_elements) {
            if (inserer_tas(&tas, liste[i])) error=1;
            ++i;
        }
        i=0;
        while (!error && tas.nbr_elements>0) {
            liste[i]=tas.tas[0];
            supprimer_tas(&tas, 0);
            ++i;
        }
        liberer_tas(&tas);
    }
    else error=1;
    return error;
}

void afficher_tas(tas_t tas) {
    int i;
    for (i=0;i<tas.nbr_elements;++i) {
        printf("%d ", tas.tas[i]);
    }
    printf("\n");
}

void afficher_liste(data_t liste[], int nbr_elements) {
    int i;
    for (i=0;i<nbr_elements;++i) {
        printf("%d ", liste[i]);
    }
    printf("\n");
}