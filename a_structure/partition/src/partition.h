#ifndef PARTITION_H
#define PARTITION_H

typedef struct part_c {
    int taille;
    int* parent;
    int* hauteur;
} part_t;

typedef struct liste_c {
    int valeur;
    struct liste_c * suivant;
} liste_t;

typedef struct classe_c {
    int* liste;
    int taille;
} classe_t;

part_t creer_part(int);
int recuperer_classe(part_t, int);
void fusion_classe(part_t, int, int);

int inserer_liste(liste_t **, int);

liste_t** creer_tab(part_t);
classe_t lister_classe(part_t, int);
classe_t* lister_partition(part_t);
void parcours_rec(liste_t**, int, classe_t*);

void liberer_part (part_t);
void liberer_liste(liste_t*);
void liberer_tableau(liste_t**, int);
void liberer_classe(classe_t);
void liberer_tableau_classe(classe_t*, int);


void afficher_part(part_t);
void afficher_tableau(liste_t**);
void afficher_classe(classe_t);
void afficher_tableau_classe(classe_t*, int);

#endif