#include <stdio.h>
#include <stdlib.h>
#include "labyrinthe.h"

laby_t init_laby(int hauteur, int largeur) {
    int i, j, noeud=0, nbr_arretes=0;
    laby_t labyrinthe;
    labyrinthe.hauteur=hauteur;
    labyrinthe.largeur=largeur;
    int dim=hauteur*largeur;
    labyrinthe.graphe.nbr_noeuds=dim;
    labyrinthe.graphe.arrete=(arrete_t*)malloc((2*dim-hauteur-largeur)*sizeof(arrete_t));
    if (labyrinthe.graphe.arrete != NULL) {
        for (i=0; i<hauteur-1; ++i) {
            for (j=0; j<largeur-1; ++j) {
                labyrinthe.graphe.arrete[nbr_arretes].A=noeud;
                labyrinthe.graphe.arrete[nbr_arretes].B=noeud+1;
                ++nbr_arretes;
                labyrinthe.graphe.arrete[nbr_arretes].A=noeud;
                labyrinthe.graphe.arrete[nbr_arretes].B=noeud+largeur;
                ++nbr_arretes;
                ++noeud;
            }
            labyrinthe.graphe.arrete[nbr_arretes].A=noeud;
            labyrinthe.graphe.arrete[nbr_arretes].B=noeud+largeur;
            ++nbr_arretes;
            ++noeud;
        }
        i=largeur-1;
        for (j=0; j<largeur-1; j++) {
            labyrinthe.graphe.arrete[nbr_arretes].A=noeud;
            labyrinthe.graphe.arrete[nbr_arretes].B=noeud+1;
            ++nbr_arretes;
            ++noeud;
        }
    }
    labyrinthe.graphe.nbr_arretes=nbr_arretes;
    return labyrinthe;
}
/*
void direction(laby_t labyrinthe) {

}

void init_carac_laby(laby_t labyrinthe) {

}*/