#include <stdio.h>
#include <stdlib.h>
#include "partition.h"
#define TAILLE 10

/* penser à vérifier (part.parent != NULL && part.hauteur != NULL)*/
part_t creer_part(int n) {
    part_t part;
    int i;
    part.taille = n;
    part.parent = (int*)malloc(n*sizeof(int));
    if (part.parent != NULL) {
        part.hauteur = (int*)malloc(n*sizeof(int));
        if (part.hauteur != NULL) {
            if (part.parent!=NULL &&& part.hauteur!=NULL) {
                for (i=0;i<n;++i) {
                    part.parent[i]=i;
                    part.hauteur[i]=1;
                }
            }
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
    if (i!=j) {
        if (part.hauteur[i] < part.hauteur[j]) part.parent[i]=j;
        else {
            part.parent[j]=i;
            if (part.hauteur[i] == part.hauteur[j]) ++part.hauteur[i];
        }
    }
}

void liberer_part(part_t part) {
    free(part.parent);
    free(part.hauteur);
}

/* penser à vérifier error*/
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

/* penser à vérifier tab != NULL*/
liste_t** creer_tab(part_t part) {
    liste_t** tab = (liste_t**)malloc(part.taille*sizeof(liste_t*));
    if (tab!=NULL) {
        int i, error=0;
        for (i=0;i<part.taille;++i) {
            tab[i]=NULL;
        }
        for (i=0;i<part.taille;++i) {
            error=inserer_liste(&(tab[part.parent[i]]),i);
        }
        if (error) tab = NULL;
    }
    return tab;
}

/* penser à vérifier classe.liste != NULL*/
classe_t lister_classe(part_t part, int i) {
    liste_t** tab=creer_tab(part); 
    classe_t classe;
    classe.liste=(int*)malloc(part.taille*sizeof(int));
    if (tab == NULL) classe.liste = NULL;
    if (classe.liste != NULL) {
        classe.taille=0;
        parcours_rec(tab, recuperer_classe(part, i), &classe);
        liberer_tableau(tab, part.taille);
    }
    return classe;
}

void parcours_rec(liste_t** tab, int i, classe_t* classe) {
    liste_t* cour=tab[i];
    while (cour!=NULL) {
        classe->liste[classe->taille]=cour->valeur;
        ++(classe->taille);
        if (cour->valeur != i) parcours_rec(tab, cour->valeur, classe);
        cour=cour->suivant;
    }
}

/* penser à vérifier tableau_classe != NULL*/
classe_t* lister_partition(part_t part) {
    int i, error = 0;
    liste_t** tab=creer_tab(part);
    if (tab == NULL) error=1;
    classe_t* tableau_classe=(classe_t*)malloc(part.taille*sizeof(classe_t));
    if (!error && tableau_classe != NULL) {
        for (i=0;i<part.taille;++i) {
            tableau_classe[i].liste=NULL;
            if (i==part.parent[i]) {
                tableau_classe[i].liste=(int*)malloc(part.taille*sizeof(int));
                if (tableau_classe[i].liste == NULL) error=1;
                else {
                    tableau_classe[i].taille=0;
                    parcours_rec(tab, i, &tableau_classe[i]);
                }
            }
        }
    }
    if (error) tableau_classe = NULL;
    liberer_tableau(tab, part.taille);
    return tableau_classe;
}

void liberer_liste(liste_t* l)
{
    liste_t *cour = l, *temp = NULL;
    while (cour != NULL)
    { 
        temp = cour;
        cour = cour->suivant;
        free(temp);
    }
}

void liberer_tableau(liste_t** tab, int taille) {
    int i;
    for (i=0;i<taille;++i) {
        if (tab[i]!=NULL) liberer_liste(tab[i]);
    }
    free(tab);
}

void liberer_classe(classe_t classe) {
    free(classe.liste);
}

void liberer_tableau_classe(classe_t* tableau_classe, int taille) {
    int i;
    for (i=0;i<taille;++i) {
        free(tableau_classe[i].liste);
    }
    free(tableau_classe);
}

void afficher_part(part_t part) {
    FILE* fichier = fopen("file/partition.dot","w+");
    int i;
    if (fichier != NULL) {
        fprintf(fichier, "digraph Partition {\n");
        if (part.parent != NULL) {
            for (i=0;i<part.taille;++i) {
                fprintf(fichier, "\t%d -> %d;\n", i, part.parent[i]);
            }
            fprintf(fichier, "}\n");
        }
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

void afficher_classe(classe_t classe) {
    int i;
    for (i=0;i<classe.taille;++i) {
        printf("%d ", classe.liste[i]);
    }
    printf("\n");
}

void afficher_tableau_classe(classe_t* tableau_classe, int taille) {
    int i,j;
    for (i=0;i<taille;++i) {
        if (tableau_classe[i].liste!=NULL) {
            printf("Classe : %d\n", i);
            for(j=0;j<tableau_classe[i].taille;++j) {
                printf("%d ", tableau_classe[i].liste[j]);
            }
            printf("\n");
        }
    }
}