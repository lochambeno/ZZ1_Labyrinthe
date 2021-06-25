#include <stdio.h>
#include <stdlib.h>
#include "parcours.h"

int* liste_voisins(laby_t laby, int noeud, int* taille) {
    int* liste = (int*)malloc(4*sizeof(int));
    *taille=0;
    if (liste != NULL) {
        int NSEO=laby.caracteristique[noeud].NSEO;
        if (NSEO & 8) {
            liste[*taille]=noeud-laby.largeur;
            ++(*taille);
        }
        if (NSEO & 4) {
            liste[*taille]=noeud+laby.largeur;
            ++(*taille);
        }
        if (NSEO & 2) {
            liste[*taille]=noeud+1;
            ++(*taille);
        }
        if (NSEO & 1) {
            liste[*taille]=noeud-1;
            ++(*taille);
        }
    }
    return liste;
}

void explorer(laby_t laby, int** marquage, int noeud, exploration_t* exploration) {
    (*marquage)[noeud]=1;
    exploration->liste[exploration->taille]=noeud;
    ++(exploration->taille);
    //deplacer(noeud);
    int taille=0, i;
    int* liste = liste_voisins(laby, noeud, &taille);
    if (liste != NULL) {
        for (i=0; i<taille; ++i) {
            if (!(*marquage)[liste[i]]) {
                explorer(laby,marquage,liste[i], exploration);
                exploration->liste[exploration->taille]=noeud;
                ++(exploration->taille);
            }
        }
        //deplacer(noeud);
        free(liste);
    }
    //exploration->liste[exploration->taille]=noeud;
    //++(exploration->taille);
}

exploration_t parcours_prof(laby_t laby) {
    exploration_t exploration;
    exploration.taille=0;
    exploration.liste = (int*)malloc(4*laby.graphe.nbr_noeuds*sizeof(int));
    if (exploration.liste != NULL) {
        int* marquage = (int*)malloc(laby.graphe.nbr_noeuds*sizeof(int));
        if (marquage != NULL) {
            int i;
            for (i=0; i<laby.graphe.nbr_noeuds; ++i) {
                marquage[i]=0;
            }
            for (i=0; i<laby.graphe.nbr_noeuds; ++i) {
                if (!marquage[i]) {
                    explorer(laby, &marquage, i, &exploration);
                }
            }
            free(marquage);
        }
    }
    return exploration;
}