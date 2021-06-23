#include <stdio.h>
#include <stdlib.h>
#include "tas_noeuds.h"

tas_t init_tas(int taille){
	tas_t a_init;
	
	a_init.tas = (data_t *) malloc(sizeof(data_t)*taille);
	a_init.nbr_elements = 0;
	a_init.taille = taille;

	if(a_init.tas == NULL){
		a_init.taille = 0;
	}

	return a_init;
}

//creer un tas avec des elements contenus dans un tableau de taille taille
/*tas_t creer_tas(data_t tab[], int taille){
	tas_t a_init;
	int i;

	a_init.tas = (data_t *) malloc(sizeof(data_t)*taille);
	a_init.nbr_elements = 0;
	a_init.taille = 0;

	if(a_init.tas != NULL){
		a_init.taille = taille;
		for(i = 0; i<taille; i++){
			inserer_tas(&a_init, tab[i]);
		}
	}

	return a_init;
}*/

void liberer_tas(tas_t * a_liberer){
	free(a_liberer->tas);
	a_liberer->tas = NULL;

	a_liberer->nbr_elements = 0;
	a_liberer->taille = 0;
}

int parent(int fils){
	return (fils-1)/2;
}

int enfant_G(int parent){
	return 2*parent + 1;
}

int enfant_D(int parent){
	return 2*parent + 2;
}

void echange(data_t * a, data_t * b){
	data_t c = *a;
	*a = *b;
	*b = c;
}

//on insere l'element a la fin du tas et on le fait remonter jusqu'a
//ce qu'il atteigne une position valide, renvois 0 en cas de reussite et 1 sinon
//complexite : o(log(n))
int inserer_tas(tas_t * tas, data_t valeur, int ** adresses_noeuds){
	int i = tas->nbr_elements;
	
	//pointeur permettant le realloc au besoin
	data_t * temp = NULL;
	int nouvelle_taille,
		erreur = 0;

	if(tas->nbr_elements == tas->taille){
		nouvelle_taille = 1.5 * tas->taille;

		temp = (data_t *) realloc(tas->tas, nouvelle_taille * sizeof(data_t));
		if(temp != NULL){
			tas->tas = temp;
			tas->taille = nouvelle_taille;
		}
	}

	//si la reallocation echoue alors taille et nbr_element seront toujours
	//egaux donc on pourra eviter de faire l'insertion
	if(tas->nbr_elements < tas->taille){
		tas->tas[i] = valeur;
		(*adresses_noeuds)[valeur.id_noeud] = i;

		while(tas->tas[i].poids < tas->tas[parent(i)].poids){
			echange(&(tas->tas[i]), &(tas->tas[parent(i)]));

			(*adresses_noeuds)[tas->tas[i].id_noeud] = parent(i);
			(*adresses_noeuds)[tas->tas[parent(i)].id_noeud] = i;

			i = parent(i);
		}
		tas->nbr_elements += 1;
	}
	else{
		erreur = -1;
	}

	return erreur;
}

//renvois l'adresse de l'element le plus petit dans le tas
int min_tas(tas_t tas, int el1, int el2){
	int min = el1;

	if(tas.tas[el2].poids < tas.tas[el1].poids){
		min = el2;
	}

	return min;
}

int est_vide_tas(tas_t tas){
	return tas.nbr_elements <= 0;
}

data_t * sommet_tas(tas_t * tas){
	data_t * sortie = NULL;
	
	if(tas->nbr_elements > 0)
		sortie = &(tas->tas[0]);

	return sortie;
}

//se fait avec l'adresse de l'element
//on insere le dernier element du tas a la place de celui a supprimer
//et on le fait redescendre a un emplacement valide
//complexite : o(log(n))
void supprimer_tas(tas_t * tas, int ** adresses_noeuds){ 
	//idee on ecrase l'element a supprimer avec l'element en fin
	//puis on fait descendre l'element en l'echangeant avec son 
	//fils le plus petit (et inferieur a lui)

	int a_traite = 0,//a_supprime,
		a_echange,
		enfant_droite,
		enfant_gauche,
		fin = 0;

	if(!est_vide_tas(*tas)){
		//si l'adresse a supprimer est valide (si y a un element), on reduit de 1 le nombre d'element
		//dans le tas et on ecrase l'element a supprimer par le dernier element
		tas->nbr_elements = tas->nbr_elements - 1;

		(*adresses_noeuds)[tas->tas[0].id_noeud] = -2;
		tas->tas[a_traite] = tas->tas[tas->nbr_elements];

		(*adresses_noeuds)[tas->tas[0].id_noeud] = 0;

		do{
			enfant_droite = enfant_D(a_traite);
			enfant_gauche = enfant_G(a_traite);

			//on verifie si le fils de gauche est valide, s'il ne l'es pas il est
			//inutile de verifier pour le fils de droite
			if(enfant_gauche<tas->nbr_elements){
				
				//si les deux fils sont valides, on recupere l'adresse du minimum
				//entre les deux et on l'echange avec l'element en cours de traitement
				//si il est plus petit que celui-ci
				if(enfant_droite<tas->nbr_elements){
					a_echange = min_tas(*tas, enfant_droite, enfant_gauche);
					if(tas->tas[a_echange].poids < tas->tas[a_traite].poids){
						
						(*adresses_noeuds)[tas->tas[a_echange].id_noeud] = a_traite;
						(*adresses_noeuds)[tas->tas[a_traite].id_noeud] = a_echange;

						echange(&(tas->tas[a_echange]), &(tas->tas[a_traite]));
						a_traite = a_echange;
					}
					else{
						fin = 1;
					}
				}

				//sinon on echange directement le fils de gauche avec l'element
				//a traite s'il est plus petit que celui-ci
				else{
					if(tas->tas[enfant_gauche].poids < tas->tas[a_traite].poids){
						(*adresses_noeuds)[tas->tas[enfant_gauche].id_noeud] = a_traite;
						(*adresses_noeuds)[tas->tas[a_traite].id_noeud] = enfant_gauche;

						echange(&(tas->tas[enfant_gauche]), &(tas->tas[a_traite]));
						a_traite = enfant_gauche;
					}
					//sinon il n'y a pas de fils valides pour faire descendre l'element
					//donc on arrete l'algorithme
					else{
						fin = 1;
					}
				}
			}
			else{
				fin = 1;
			}
		}while(!fin);
	}
}

/*int tri_tas(data_t (*tab)[], int nbr_element){
	tas_t tas = creer_tas(*tab, nbr_element);
	int erreur = 0,
		i;

	if(tas.nbr_elements > 0){
		for(i=0; i<nbr_element; i++){
			(*tab)[i] = *sommet_tas(&tas);
			supprimer_tas(&tas);
		}
	}
	else{
		erreur = 1;
	}

	liberer_tas(&tas);

	return erreur;
}*/
