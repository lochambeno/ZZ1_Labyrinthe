#include <stdio.h>
#define N 30
#define M 50



void tore(int* i, int* j)
{
    if(*i==-1)
        *i=N-1;
    if(*i==N)
        *i=0;
    if(*j==-1)
        *j=M-1;
    if(*j==M)
        *j=0;
    
}

int nbr_voisin(int i, int j, int** tab)
{
    int voisin_i, voisin_j, voisin=0, iter_i, iter_j;

    for(iter_i=-1; iter_i<2; iter_i++)
    {
        for(iter_j=-1; iter_j<2; iter_j++)
        {
            if(!(iter_i==0 && iter_j==0))
            {    
                voisin_i=i+iter_i;
                voisin_j=j+iter_j;
                tore(&voisin_i, &voisin_j);
                voisin+=tab[voisin_i][voisin_j];
            }
        }
    }
    return voisin;
}