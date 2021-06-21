#include <stdio.h>
#include <stdlib.h>
#include "partition.h"

int main() {
    part_t part = creer_part(11);
    fusion_classe(part, 0, 1);
    fusion_classe(part, 2, 3);
    fusion_classe(part, 10, 3);
    fusion_classe(part, 5, 9);
    fusion_classe(part, 4, 6);
    fusion_classe(part, 8, 7);
    fusion_classe(part, 9, 7);
    fusion_classe(part, 6, 8);
    afficher_part(part);
    //liste_t**tab=creer_tab(part);
    //afficher_tableau(tab);
    lister_classe(part,8);
    liberer_part(part);
    return 0;
}