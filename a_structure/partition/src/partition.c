#include <stdio.h>
#include <stdlib.h>
#include "partition.h"
#define TAILLE 10

part_t creer_part(int n) {
    part_t part;
    int i;
    part.taille = n;
    part.parent = (int*)malloc(n*sizeof(int));
    part.hauteur = (int*)malloc(n*sizeof(int));
    if (part.parent!=NULL &&& part.hauteur!=NULL) {
        for (i=0;i<n;++i) {
            part.parent[i]=i;
            part.hauteur[i]=1;
        }
    }
    return part;
}

int recuperer_classe(part_t part, int i) {
    while (part.parent[i]!=i) i=part.parent[i];
    return i;
}

void fusion_classe(part_t part, int i, int j) {
    i=recuperer_classe(part, i);
    j=recuperer_classe(part, j);
    if (part.hauteur[i] < part.hauteur[j]) part.parent[i]=j;
    else 
    {
        part.parent[j]=i;
        if (part.hauteur[i] == part.hauteur[j]) ++part.hauteur[i];
    }
}

void liberer_part(part_t part) {
    free(part.parent);
    free(part.hauteur);
}

int inserer_liste(liste_t **p_l, int valeur) {
    liste_t *cellule = (liste_t*)malloc(sizeof(liste_t));
    int error=0;
    if (cellule==NULL) error=1;
    else {
        cellule->valeur=valeur;
        cellule->suivant=*p_l;
        *p_l=cellule;
    }
    return error;
}

liste_t** creer_tab(part_t part) {
    liste_t** tab = (liste_t**)malloc(part.taille*sizeof(liste_t*));
    int i;
    for (i=0;i<part.taille;++i) {
        inserer_liste(&(tab[part.parent[i]]),i);
    }
    return tab;
}

void lister_classe(part_t part, int i) {
    liste_t** tab=creer_tab(part);
    parcours_rec(tab, part.parent[i]);
    printf("\n");
}

void parcours_rec(liste_t** tab, int i) {
    liste_t* cour=tab[i];
    while (cour!=NULL) {
        printf("%d ", cour->valeur);
        if (cour->valeur != i) parcours_rec(tab, cour->valeur);
        cour=cour->suivant;
    }
}

void afficher_part(part_t part) {
    FILE* fichier = fopen("src/affichage.dot","w+");
    int i;
    if (fichier != NULL) {
        fprintf(fichier, "digraph Partition {\n");
        for (i=0;i<part.taille;++i) {
            fprintf(fichier, "\t%d -> %d;\n", i, part.parent[i]);
        }
        fprintf(fichier, "}\n");
    }
    fclose(fichier);
}

void afficher_tableau(liste_t** tab) {
    int i;
    for (i=0;i<11;++i) {
        liste_t* cour = tab[i];
        while (cour!=NULL) {
            printf("%d ", cour->valeur);
            cour=cour->suivant;
        }
        printf("\n");
    }
}