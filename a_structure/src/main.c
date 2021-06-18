#include <stdio.h>
#include <stdlib.h>
#include "tas_binaire.h"

int main() {
    tas_t tas;
    init_tas(40, &tas);
    inserer_tas(&tas, 3);
    afficher_tas(tas);
    inserer_tas(&tas, 5);
    afficher_tas(tas);
    inserer_tas(&tas, 2);
    afficher_tas(tas);
    inserer_tas(&tas, 4);
    afficher_tas(tas);
    supprimer_tas(&tas, 1);
    afficher_tas(tas);
    return 0;
}