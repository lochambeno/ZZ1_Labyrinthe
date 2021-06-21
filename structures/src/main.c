#include "partition.h"
#include <stdio.h>

int main()
{	
	part_t part = init_part(11);

	fusion_part(&part, 0, 1);
	fusion_part(&part, 2, 3);
	fusion_part(&part, 10, 3);
	fusion_part(&part, 5, 9);
	fusion_part(&part, 4, 6);
	fusion_part(&part, 8, 7);
	fusion_part(&part, 9, 7);
	fusion_part(&part, 6, 8);

	liste_t** liste = lister_classes(part);


	afficher_part(part);

	liberer_classes(liste, part.taille);
	liberer_partition(&part);


	return 0;
}