#ifndef LISTE_H
#define LISTE_H

typedef int data_l;

typedef struct liste_c{
    data_l val;
    struct liste_c * suiv;
} liste_t;

/* **************************************************************************************************** *
   Input :		Aucun

   creer_liste :	Renvois NULL

   Output :		Une liste vide
 * **************************************************************************************************** */

liste_t * creer_liste();


/* **************************************************************************************************** *
   Input :		l'adresse d'une liste l

   liberer_liste :	parcourt la liste en libérant chacun des éléments qui la compose

   Output :		void
 * **************************************************************************************************** */

void liberer_liste(liste_t **);


/* **************************************************************************************************** *
   Input :		trois entier v, i et j

   nouv_cellule :	créer une nouvelle cellule ayant pour valeur :
			val = v, ci = i et cj = j

   Output :		une cellule ou NULL en cas d'erreur d'allocation
 * **************************************************************************************************** */

liste_t * nouv_cellule(data_l);


/* **************************************************************************************************** *
   Input :		l'adresse d'une liste l. Les entiers  a_inserer, i et j.

   insertion :		insertion va utiliser la fonction nouv_cellule pour créer une cellule
			avec les paramètres a_inserer, i et j. Si l'allocation s'est bien passée, elle
			va insérer le nouvel élément en tête de l (ou avant l'élément pointé par l).

   Output :		1 si l'allocation s'est bien passée, 0 sinon
 * **************************************************************************************************** */

int insertion(liste_t **, data_l);

/* **************************************************************************************************** *
   Input :		l'adresse de l'élément à supprimer

   suppression :	supprime l'élément de la liste et change le pointeur par l'adresse de l'élément 
			suivant	

   Output :	        void
 * **************************************************************************************************** */

void suppression(liste_t **);

/* **************************************************************************************************** *
   Input :		la liste l a afficher

   afficher_liste :	parcourt la liste l et affiche tous ses éléments dans le terminal

   Output :		void
 * **************************************************************************************************** */

void afficher_liste(liste_t *);

/* **************************************************************************************************** *
   Input :		une liste l et un nom de fichier sous la forme d'une chaine de caractère

   sauv_liste :		

   Output :		0 si le fichier n'a pas pu être créé/modifié et 1 sinon
 * **************************************************************************************************** */


#endif
