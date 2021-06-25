#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "kruskal.h"

void echange_arrete(graphe_t* p_graphe, int i, int j) {
    arrete_t temp = p_graphe->arrete[i];
    p_graphe->arrete[i] = p_graphe->arrete[j];
    p_graphe->arrete[j] = temp;
}

void fisher_yate(graphe_t* p_graphe) {
    int i;
    for (i=p_graphe->nbr_arretes-1; i>0; --i) {
        echange_arrete(p_graphe, rand()%i, i);
    }
}

/* penser à vérifier arbre_couvrant.arrete != NULL */
graphe_t kruskal(graphe_t graphe, int proba) {
    int i;
    //srand(time(NULL));
    fisher_yate(&graphe);
    part_t part = creer_part(graphe.nbr_noeuds);
    graphe_t arbre_couvrant;
    arbre_couvrant.arrete=(arrete_t*)malloc(graphe.nbr_noeuds*4*sizeof(arrete_t));
    arbre_couvrant.nbr_noeuds=graphe.nbr_noeuds;
    arbre_couvrant.nbr_arretes=0;
    if (arbre_couvrant.arrete != NULL) {
        if (part.parent != NULL && part.hauteur != NULL) {
            for (i=0; i<graphe.nbr_arretes; ++i) {
                if (recuperer_classe(part, graphe.arrete[i].A) != recuperer_classe(part, graphe.arrete[i].B)) {
                    fusion_classe(part, graphe.arrete[i].A, graphe.arrete[i].B);
                    ajouter_arrete(&arbre_couvrant, graphe.arrete[i].A, graphe.arrete[i].B);
                }
                else {
                    if (rand()%100<proba) {
                        ajouter_arrete(&arbre_couvrant, graphe.arrete[i].A, graphe.arrete[i].B);
                    }
                }
            }
        }
        else arbre_couvrant.arrete=NULL;
    }
    liberer_part(part);
    return arbre_couvrant;
} 

void afficher_arbre_couvrant(graphe_t graphe) {
    FILE* fichier = fopen("file/arbre_couvrant.dot","w+");
    int i;
    if (fichier != NULL) {
        fprintf(fichier, "graph Arbre_couvrant {\n");
        for (i=0;i<graphe.nbr_arretes;++i) {
            fprintf(fichier, "\t%d -- %d;\n", graphe.arrete[i].A, graphe.arrete[i].B);
        }
        for (i=0;i<graphe.nbr_noeuds;++i) {
            fprintf(fichier, "\t%d;\n", i);
        }
        fprintf(fichier, "}\n");
    }
    fclose(fichier);
}