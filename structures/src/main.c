#include "tas.h"
#include "partition.h"
#include <stdio.h>

int main(){	
	/*data_t tab[] = {14, 4, 5, 10, 11, 23, 6, 12, 20};

	tri_tas(&tab, 9);
	for(int i=0; i<9; i++){
		printf("%d\n", tab[i]);
	}*/
	
	partition_t partition;
	partition = init_partition(11);

	fusion_partition(0, 1, &partition);
	fusion_partition(2, 3, &partition);
	fusion_partition(10, 3, &partition);
	fusion_partition(5, 9, &partition);
	fusion_partition(4, 6, &partition);
	fusion_partition(8, 7, &partition);
	fusion_partition(9, 7, &partition);
	fusion_partition(6, 8, &partition);

	creer_affichage_partition(partition);

	return 0;
}