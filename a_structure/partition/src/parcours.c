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

void explorer(laby_t laby, int** marquage, int noeud, int** exploration, int* sommet) {
    (*marquage)[noeud]=1;
    (*exploration)[*sommet]=noeud;
    ++(*sommet);
    //deplacer(noeud);
    int taille=0, i;
    int* liste = liste_voisins(laby, noeud, &taille);
    if (liste != NULL) {
        for (i=0; i<taille; ++i) {
            if (!(*marquage)[liste[i]]) {
                explorer(laby,marquage,liste[i], exploration, sommet);
            }
        }
        //deplacer(noeud);
        free(liste);
    }
}

int* parcours_prof(laby_t laby) {
    int* exploration = (int*)malloc(laby.graphe.nbr_noeuds*sizeof(int));
    if (exploration != NULL) {
        int* marquage = (int*)malloc(laby.graphe.nbr_noeuds*sizeof(int));
        if (marquage != NULL) {
            int i, sommet=0;
            for (i=0; i<laby.graphe.nbr_noeuds; ++i) {
                marquage[i]=0;
            }
            for (i=0; i<laby.graphe.nbr_noeuds; ++i) {
                if (!marquage[i]) {
                    explorer(laby, &marquage, i, &exploration, &sommet);
                }
            }
            free(marquage);
        }
    }
    return exploration;
}