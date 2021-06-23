#include <stdio.h>
#include <stdlib.h>
#include "labyrinthe.h"

/* penser à vérifier labyrinthe.graphe.arrete != NULL */
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

/* penser à vérifier labyrinthe.caracteristique!=NULL */
void init_carac_laby(laby_t* labyrinthe) {
    int i;
    labyrinthe->caracteristique = (carac_t*)malloc(labyrinthe->graphe.nbr_noeuds*sizeof(carac_t));
    if (labyrinthe->caracteristique != NULL) {
        for (i=0; i<labyrinthe->graphe.nbr_noeuds; ++i) {
            labyrinthe->caracteristique[i].NSEO=0;
        }
        for (i=0; i<labyrinthe->graphe.nbr_arretes; ++i) {
            if (labyrinthe->graphe.arrete[i].A == labyrinthe->graphe.arrete[i].B-1) {
                labyrinthe->caracteristique[labyrinthe->graphe.arrete[i].A].NSEO+=2;
                labyrinthe->caracteristique[labyrinthe->graphe.arrete[i].B].NSEO+=1;
            }
            else {
                labyrinthe->caracteristique[labyrinthe->graphe.arrete[i].A].NSEO+=4;
                labyrinthe->caracteristique[labyrinthe->graphe.arrete[i].B].NSEO+=8;
            }
        }
    }
}

void afficher_carac(laby_t laby) {
    int i;
    for (i=0; i<laby.graphe.nbr_noeuds; ++i) {
        printf("%d ", laby.caracteristique[i].NSEO);
    }
    printf("\n");
}

void liberer_labyrinthe(laby_t* labyrinthe) {
    free(labyrinthe->caracteristique);
    liberer_graphe(&labyrinthe->graphe);
}

laby_t creer_laby(int hauteur, int largeur) {
    laby_t grille = init_laby(hauteur, largeur), laby;
    laby.graphe = kruskal(grille.graphe);
    laby.hauteur=hauteur;
    laby.largeur=largeur;
    init_carac_laby(&laby);
    liberer_graphe(&grille.graphe);
    return laby;
}