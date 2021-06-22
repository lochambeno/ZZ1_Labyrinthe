#include <stdio.h>
#include <stdlib.h>
#include "partition.h"
#include "connexe.h"

int main() {
    /*
    part_t part = creer_part(11);
    fusion_classe(part, 0, 1);
    fusion_classe(part, 2, 3);
    fusion_classe(part, 10, 3);
    fusion_classe(part, 5, 9);
    fusion_classe(part, 4, 6);
    fusion_classe(part, 8, 7);
    fusion_classe(part, 9, 7);
    fusion_classe(part, 6, 8);
    int* liste=NULL, taille;
    lister_classe(part, 7, &liste, &taille);
    afficher_classe(liste, taille);
    afficher_part(part);
    //liste_t**tab=creer_tab(part);
    //afficher_tableau(tab);
    //lister_partition(part);
    //int** mat = mat_adj(10);
    //afficher_mat(mat, 10);
    //liberer_mat(mat, 10);
    */
    int taille=5;
    /*int** mat=mat_adj(taille);
    afficher_graphe_mat(mat, taille);
    part_t comp_connexe=mat_comp_connexe(mat, 11);
    afficher_part(comp_connexe);
    lister_partition(comp_connexe);
    liberer_mat(mat, taille);
    liberer_part(comp_connexe);
    */
    graphe_t graphe=init_graphe(taille);
    afficher_graphe(graphe);
    
    part_t comp_connexe=graphe_comp_connexe(graphe);
    afficher_part(comp_connexe);
    /*
    classe_t classe = lister_classe(comp_connexe,0);
    afficher_classe(classe);
    liberer_classe(classe);
    */
    /*
    classe_t* classes = lister_partition(comp_connexe);
    afficher_tableau_classe(classes,taille);
    liberer_tableau_classe(&classe,taille);
    */

    //afficher_graphe_comp_connexe(graphe, 0);
    lister_partition(comp_connexe);
    //liberer_part(comp_connexe);
    liberer_graphe(&graphe);
    return 0;
}