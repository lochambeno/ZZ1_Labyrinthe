#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "connexe.h"
 
/* penser à vérifier mat != NULL*/
int** mat_adj(int taille) {
    int i,j,error=0;
    int** mat=(int**)malloc(taille*sizeof(int*));
    srand(time(NULL));
    if (mat!=NULL) {
        for (i=0;i<taille;++i) {
            mat[i]=(int*)malloc(taille*sizeof(int));
            if (mat[i]==NULL) {
                error=1;
            }
            else {
                for (j=0;j<i;++j) {
                    mat[i][j]=rand()%2;
                }
            }
        }
    }
    if (error) mat=NULL;
    return mat;
}

part_t mat_comp_connexe(int** mat, int taille) {
    int i,j;
    part_t comp_connexe = creer_part(taille);
    for (i=0;i<taille;++i) {
        for (j=0;j<i;++j) {
            if (mat[i][j]) {
                fusion_classe(comp_connexe, i, j);
            }
        }
    }
    return comp_connexe;
}

void afficher_mat(int** mat, int taille) {
    int i,j;
    for (i=0;i<taille;++i) {
        for (j=0;j<i;++j) {
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
}

void liberer_mat(int** mat, int taille) {
    int i;
    for (i=0;i<taille;++i) {
        free(mat[i]);
    }
    free(mat);
}

void afficher_graphe_mat(int** mat, int taille) {
    FILE* fichier = fopen("file/graphe.dot","w+");
    int i, j;
    if (fichier != NULL) {
        fprintf(fichier, "graph Graphe {\n");
        for (i=0;i<taille;++i) {
            for (j=0;j<i;++j) {
                if (mat[i][j]) {
                    fprintf(fichier, "\t%d -- %d;\n", i, j);
                }
            }
        }
        fprintf(fichier, "}\n");
    }
    fclose(fichier);
}




graphe_t init_graphe(int taille) {
    graphe_t graphe;
    graphe.nbr_noeuds=taille;
    graphe.arrete=(arrete_t*)malloc(taille*4*sizeof(arrete_t));
    int i, j, nbr_arretes=0;
    int arrete_par_noeuds[taille];
    for (i=0;i<taille;++i) arrete_par_noeuds[i]=0;
    srand(0);
    for (i=0;i<taille;++i) {
        for (j=i+1;j<taille;++j) {
            if (arrete_par_noeuds[i]<4 && arrete_par_noeuds[j]<4 && rand()%2) {
                graphe.arrete[nbr_arretes].A=i;
                graphe.arrete[nbr_arretes].B=j;
                ++nbr_arretes;
                ++arrete_par_noeuds[i];
                ++arrete_par_noeuds[j];
            }
        }
    }
    graphe.nbr_arretes=nbr_arretes;
    return graphe;
}

void afficher_graphe(graphe_t graphe) {
    FILE* fichier = fopen("file/graphe.dot","w+");
    int i;
    if (fichier != NULL) {
        fprintf(fichier, "graph Graphe {\n");
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

part_t graphe_comp_connexe(graphe_t graphe) {
    int i;
    part_t comp_connexe = creer_part(graphe.nbr_noeuds);
    for (i=0;i<graphe.nbr_arretes;++i) {
        fusion_classe(comp_connexe, graphe.arrete[i].A, graphe.arrete[i].B);
    }
    return comp_connexe;
}

void afficher_graphe_comp_connexe (graphe_t graphe, int m) {
    FILE* fichier = fopen("file/comp_connexe.dot","w+");
    part_t part= graphe_comp_connexe (graphe);
    int i, j;
    classe_t classe = lister_classe(part, m);
    if (fichier != NULL) {
        fprintf(fichier, "graph Composante_connexe {\n");
        for (i=0;i<graphe.nbr_arretes;++i) {
            for (j=0;j<classe.taille;++j) {
                if (classe.liste[j]==graphe.arrete[i].A) {
                    fprintf(fichier, "\t%d -- %d;\n", graphe.arrete[i].A, graphe.arrete[i].B);
                }
            }
        }
        for (j=0;j<classe.taille;++j) {
            fprintf(fichier, "\t%d;\n", classe.liste[j]);
        }
        fprintf(fichier, "}\n");
    }
    liberer_classe(classe);
    fclose(fichier);
}

void liberer_graphe(graphe_t* graphe) {
    free(graphe->arrete);
}