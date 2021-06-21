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

part_t creer_part(int);
int recuperer_classe(part_t, int);
void fusion_classe(part_t, int, int);
void liberer_part (part_t);
int inserer_liste(liste_t **, int);
liste_t** creer_tab(part_t);
void lister_classe(part_t, int);
void parcours_rec(liste_t**, int);
void afficher_part(part_t);
void afficher_tableau(liste_t**);

#endif