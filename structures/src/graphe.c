#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"


graphe_t creer_graphe(int nbr_noeuds)
{
    graphe_t graphe;
    arrete_t* tab_arrete = (arrete_t*)malloc(20*sizeof(arrete_t));
    if( tab_arrete != NULL)
    {
        graphe.tab_arretes = tab_arrete;
        graphe.nbr_arretes = 0;
        graphe.taille_tab = 20;
        graphe.nbr_noeuds = nbr_noeuds;

    }
    else graphe.taille_tab = 0;

    return graphe;
}


void creer_arrete(graphe_t* p_graphe, int a, int b)
{
    int nouvelle_taille;

    arrete_t arrete;
    arrete.a = a;
    arrete.b = b;
    if (p_graphe->nbr_arretes == p_graphe->taille_tab) 
    {
		nouvelle_taille = 1.5 * p_graphe->taille_tab;

		arrete_t* temp = (arrete_t *) realloc(p_graphe->tab_arretes, nouvelle_taille * sizeof(arrete_t));
		if(temp != NULL)
        {
			p_graphe->tab_arretes = temp;
			p_graphe->taille_tab = nouvelle_taille;
		}
    }
    (p_graphe->tab_arretes[p_graphe->nbr_arretes]).a =  arrete.a;
    (p_graphe->tab_arretes[p_graphe->nbr_arretes]).b =  arrete.b;
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


void afficher_graphe(graphe_t graphe, char* nom)
{
    int i, j;
    arrete_t* tab_arrete = graphe.tab_arretes;

    FILE *fichier;
    fichier = fopen(nom, "w");
    if(fichier != NULL)
    {
        fprintf(fichier, "graph graphe {\n");

        for(j=0; j< graphe.nbr_noeuds; ++j)
        {
            fprintf(fichier, "\t%d;\n", j);

        }

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
    for(i=0; i < graphe.nbr_arretes; ++i)
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


graphe_t kruskal(graphe_t graphe)
{
    graphe_t arbre = creer_graphe(graphe.nbr_noeuds);
    part_t part = graphe_part(arbre);
    int i;
    for(i=0; i<graphe.nbr_arretes; ++i)
    {
        if(recuperer_classe(part, graphe.tab_arretes[i].a) != recuperer_classe(part, graphe.tab_arretes[i].b))
        {
            fusion_part(&part, (graphe.tab_arretes[i]).a, (graphe.tab_arretes[i]).b);
            creer_arrete(&arbre, (graphe.tab_arretes[i]).a, (graphe.tab_arretes[i]).b);
        }
    }
    return arbre;
}