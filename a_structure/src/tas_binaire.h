#ifndef TAS_BINAIRE_H
#define TAS_BINAIRE_H

typedef int data_t;
typedef struct tas_c {
    data_t* tas;
    int nbr_elements;
    int taille;
} tas_t;

tas_t init_tas();
void liberer_tas(tas_t*);
int parent(int);
int enfant_gauche(int);
int enfant_droite(int);
void echange_tas(tas_t*, int, int);
int inserer_tas(tas_t*, data_t);
int min_enfant(tas_t, int);
void supprimer_tas(tas_t*, int );
int tri_tas(data_t liste[], int);
void afficher_tas(tas_t);
void afficher_liste(data_t liste[], int);

#endif