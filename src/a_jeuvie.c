#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#define N 30
#define M 50 

int survie[9] = {0,0,1,1,0,0,0,0,0};
int naissance[9] = {0,0,0,1,0,0,0,0,0};

void tore(int* i, int* j) {
    if (*i==N) *i=0;
    if (*i==-1) *i=N-1;
    if (*j==M) *j=0;
    if (*j==-1) *j=M-1;
}

int** init_zero() {
    int i, j;
    int** tab = (int **)malloc(N*sizeof(int *));
    for (i=0;i<N;++i) {
        tab[i] = (int*)malloc(M*sizeof(int));
        for (j=0;j<M;++j) {
            tab[i][j]=0;
        }
    }
    return tab;
}

void init_uns(int** tab) {
    tab[(int)N/2][(int)M/2]=1;
    tab[(int)N/2+1][(int)M/2]=1;
    tab[(int)N/2][(int)M/2+1]=1;
    tab[(int)N/2+1][(int)M/2+1]=1;
}

void afficher(int** tab) {
    int i, j;
    for (i=0;i<N;++i) {
        for (j=0;j<M;++j) {
            printf("%d ",tab[i][j]);
        }
        printf("\n");
    }
}

void iter_jeuvie(int** tab) {
    int i, j;
    int** voisins=init_zero();
    for (i=0;i<N;++i) {
        for (j=0;j<M;++j) {
            nbr_voisins
        }
    }
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    int** tab = init_zero();
    init_uns(tab);
    afficher(tab);
    return 0;
}