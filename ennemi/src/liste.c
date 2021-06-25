#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

liste_t * creer_liste(){
    return NULL;
}

void liberer_liste(liste_t ** liste){
    liste_t * prec = *liste;
    liste_t * temp = NULL;

    while(prec!=NULL && prec->suiv != NULL ){
        temp = prec;
        prec = prec->suiv;
        free(temp);
    }
    free(prec);
    *liste = NULL;
}

liste_t * nouv_cellule(data_l v){
  liste_t * nouv = (liste_t*) malloc(sizeof(liste_t));
  if(nouv != NULL){
    nouv->val = v;
    nouv->suiv = NULL;
  }
  return nouv;
}

int insertion(liste_t ** prec, int a_inserer){
  int retour = 1;
  liste_t * nouv = nouv_cellule(a_inserer);

  if(nouv != NULL){
    nouv->suiv = *prec;
    *prec = nouv;
  }
  else{
    free(nouv);
    retour = 0;
  }

  return retour;
}

void suppression(liste_t ** prec){

  liste_t * sauv = NULL;
  
  if(*prec != NULL){
    sauv = *prec;
    *prec = (*prec)->suiv;
    free(sauv);
  }
  
}

void afficher_liste(liste_t * prec){

  while(prec != NULL){
    printf("%d\n", (*prec).val);
    prec = prec->suiv;
  }
}


