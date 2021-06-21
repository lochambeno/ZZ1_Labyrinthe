#ifndef LISTE_H
#define LISTE_H


/* -------------------------------------------------------------------- */
/* liste_t         Structure de liste chainée                           */
/*                                                                      */
/* Champs: valeur  Valeur contenue dans la liste                        */
/*         suivant Pointeur sur la cellule suivante de la liste chainée */
/* -------------------------------------------------------------------- */

typedef struct liste
{
    int  valeur;
    struct liste * suivant;
} liste_t;

liste_t * creer_liste();
void liberer_liste(liste_t *);
void inserer(liste_t **, int);
void supprimer(liste_t **);
void afficher(liste_t *);


#endif