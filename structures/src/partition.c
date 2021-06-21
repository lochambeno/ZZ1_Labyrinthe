#include <stdio.h>
#include <stdlib.h>
#include "partition.h"



part_t init_part(int taille)
{
    int i;
    part_t part;
    part.taille = taille;
    part.parent = (int*)malloc((part.taille)*sizeof(int));

    if(part.parent == NULL) part.taille = 0;
    else
    {
        part.hauteur = (int*)malloc((part.taille)*sizeof(int));
        if(part.hauteur == NULL) 
        {
            part.taille = 0;
            free(part.parent);
        }
        else
        {
            for(i=0; i<taille; ++i)
            {
                part.parent[i] = i;
                part.hauteur[i] = 1;
            }
        }
    }
    return part;
}

void afficher_part(part_t part)
{

    int i;

    FILE *fichier;
    fichier = fopen("./file/affichage.dot", "w");
    if(fichier != NULL)
    {
        fprintf(fichier, "digraph mongraphe {\n");

        for(i = 0; i < part.taille; ++i)
        {
            fprintf(fichier, "\t%d -> %d;\n", i , part.parent[i]);
        }

        fprintf(fichier, "}");


        fclose(fichier);
    
    }
}


int recuperer_classe(part_t part, int elt)
{
    int i=elt;
    while(part.parent[i] != i)
    {
        i = part.parent[i];
    }
    return i;
}



void fusion_part(part_t* p_part, int x, int y)
{
    x = recuperer_classe(*p_part, x);
    y = recuperer_classe(*p_part, y);
    if(p_part->hauteur[x] > p_part->hauteur[y])
    {
        p_part->parent[y] = x;
    }
    else
    {
        if(p_part->hauteur[x] < p_part->hauteur[y]) p_part->parent[x] = y;
        else 
        {
            p_part->parent[y] = x;
            p_part->hauteur[x]++;
        }
    }
}