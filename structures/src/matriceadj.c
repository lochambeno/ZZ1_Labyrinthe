#include <stdio.h>
#include <stdlib.h>
#include "partition.h"



#define N 10



int** creer_adj()
{
    int i;
    int** mat = (int **)malloc(N*sizeof(int*));
    if(mat != NULL)
    {
        for(i=0; i<N; ++i)
        {
            mat[i] = (int *)malloc(N*sizeof(int));
        }
    }
    return mat;
}


void init_mat(int** mat)
{
    int i, j;
    srand(2);
    for(i=0; i<N; ++i)
    {
        for(j=0; j<i; j++)
        {
            mat[i][j] = rand()%2;
        }
    }
}



void afficher_mat(int** mat)
{

    int i, j;

    FILE *fichier;
    fichier = fopen("./file/affMat.dot", "w");
    if(fichier != NULL)
    {
        fprintf(fichier, "digraph grapheMat {\n");

        for(i = 0; i < N; ++i)
        {
            for(j = 0; j < i; ++j)
            {
                if(mat[i][j])
                {
                    fprintf(fichier, "\t%d -> %d;\n", i , j);
                }
            }
        }
        fprintf(fichier, "}");

        fclose(fichier);  
    }
}

void compoConnexe(int** mat)
{
    part_t part = init_part(N);
    int i, j;

    for(i=0; i<N; ++i)
    {
        for(j=0; j < i; j++)
        {
            if(mat[i][j]) fusion_part(&part, i, j);
        }
    }
    afficher_part(part); 
}


int main()
{	

	int** mat = creer_adj();
	init_mat(mat);
	afficher_mat(mat);
    compoConnexe(mat);

	return 0;
}