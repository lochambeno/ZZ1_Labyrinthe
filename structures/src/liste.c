#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

/* -------------------------------------------------------------------- */
/* creer_liste        Crée une liste chainée vide du type liste_t       */
/*                                                                      */
/* En sortie:         Pointeur de tête de la liste sur NULL             */
/* -------------------------------------------------------------------- */

liste_t * creer_liste()
{    
    return NULL;
}


/* -------------------------------------------------------------------- */
/* liberer_liste      Libère l'espace alloué par la liste chainée       */
/*                                                                      */
/* En entrée: l       Pointeur de tête de la liste                      */
/* -------------------------------------------------------------------- */

void liberer_liste(liste_t *l)
{
    liste_t *cour = l, *temp;
    while (cour != NULL)
    {      
        temp = cour->suivant;
        free(cour);
        cour = temp;
    }
}


/* -------------------------------------------------------------------- */
/* inserer            Insère une cellule en tête de liste               */
/*                                                                      */
/* En entrée: p_l     Pointeur sur la tête de liste                     */
/*            value   Valeur à insérer                                  */
/* -------------------------------------------------------------------- */

void inserer(liste_t **p_l, int value)
{
    liste_t *cellule = (liste_t *)malloc(sizeof(liste_t));
    if (cellule == NULL)
    {
        fprintf(stderr, "Allocation impossible\n");
    }
    else
    {
        cellule->valeur=value;

        cellule->suivant=*p_l;
        *p_l=cellule;
    }
}


/* -------------------------------------------------------------------- */
/* supprimer          Supprime la cellule en tête de la liste           */
/*                                                                      */
/* En entrée: p_l     Pointeur sur la tête de liste                     */
/* -------------------------------------------------------------------- */

void supprimer(liste_t **p_l) 
{
    liste_t *temp = *p_l;

    *p_l = temp->suivant;

    free(temp);
}

/*
void afficher(liste_t * l)
{
    liste_t * cour= l;
    while (cour!=NULL)
    {
        printf("%d\n", cour->valeur);
        cour = cour->suivant;
    }
}
*/