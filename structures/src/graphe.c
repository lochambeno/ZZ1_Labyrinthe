#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"


graphe_t creer_graphe(int nbr_noeuds, int nbr_arretes)
{
    graphe_t graphe;
    arrete_t* tab_arrete = (arrete_t*)malloc(nbr_arretes*sizeof(arrete_t));
    if( tab_arrete != NULL)
    {
        graphe.tab_arretes = tab_arrete;
        graphe.nbr_arretes = 0;
        graphe.taille_tab = nbr_arretes;
        graphe.nbr_noeuds = nbr_noeuds;

    }
    else graphe.taille_tab = 0;

    return graphe;
}


void creer_arrete(graphe_t* p_graphe, int a, int b)
{
    arrete_t arrete;
    arrete.a = a;
    arrete.b = b;
    p_graphe->tab_arretes[p_graphe->nbr_arretes] =  arrete;
    (p_graphe->nbr_arretes)++;
}



void init_graph(graphe_t* p_graphe)
{
    int i;

    for(i=0; i < p_graphe->taille_tab; ++i)
    {
        creer_arrete(p_graphe, rand()%(p_graphe->nbr_noeuds), rand()%(p_graphe->nbr_noeuds));
    }
}


void afficher_graphe(graphe_t graphe)
{
    int i;
    arrete_t* tab_arrete = graphe.tab_arretes;

    FILE *fichier;
    fichier = fopen("./file/aff_graphe.dot", "w");
    if(fichier != NULL)
    {
        fprintf(fichier, "graph graphe {\n");

        for(i = 0; i < graphe.nbr_arretes; ++i)
        {
            fprintf(fichier, "\t%d -- %d;\n", (tab_arrete[i]).a , (tab_arrete[i]).b);
        }

        fprintf(fichier, "}");

        fclose(fichier);
    
    }
}

part_t graphe_part(graphe_t graphe)
{
    part_t part = init_part(graphe.nbr_noeuds);
    int i;
    for(i=0; i < graphe.taille_tab; ++i)
    {
        fusion_part(&part, (graphe.tab_arretes[i]).a, (graphe.tab_arretes[i]).b);
    }
    return part;
}

int in_liste(liste_t liste, int x)
{
    int in = 0;
    liste_t* cour = &liste;
    while(cour != NULL && in==0)
    {
        if(cour->valeur == x) in = 1;
        else cour = cour->suivant;
    }
    return in;
}


void compo_connexe(part_t part, graphe_t graphe, int elt)
{
    FILE *fichier;
    fichier = fopen("./file/aff_sous_graphe.dot", "w");
    if(fichier != NULL)
    {
        fprintf(fichier, "graph graphe_connexe {\n");
        liste_t** classes = lister_classes(part);
        int i, classe_elt = recuperer_classe(part, elt);
        for(i=0; i<graphe.nbr_arretes; ++i)
        {
            if((in_liste(*classes[classe_elt], (graphe.tab_arretes[i]).a)) && (in_liste(*classes[classe_elt], (graphe.tab_arretes[i]).b)))
            {
                fprintf(fichier, "\t%d -- %d;\n", (graphe.tab_arretes[i]).a , (graphe.tab_arretes[i]).b);

            }
        
        
        }
        fprintf(fichier, "}");

        fclose(fichier);
    }
    
}

