#ifndef ZZ1_PROJET_TAS_H
#define ZZ1_PROJET_TAS_H

typedef struct data_c{
	int id_noeud;
	int poids;
	int parent;
}data_t;

typedef data_t noeud_t;

typedef struct tas_c{
	data_t * tas;
	int nbr_elements; 
	int taille;
}tas_t;

tas_t init_tas(int);
tas_t creer_tas(data_t tab[], int);
void liberer_tas(tas_t *);

int parent(int);
int enfant_G(int);
int enfant_D(int);

void echange(data_t *, data_t *);
int inserer_tas(tas_t *, data_t, int **);

int est_vide_tas(tas_t);
int min_tas(tas_t, int, int);

data_t * sommet_tas(tas_t *);
void supprimer_tas(tas_t *, int **);

int tri_tas(data_t (*tab)[], int);

#endif
