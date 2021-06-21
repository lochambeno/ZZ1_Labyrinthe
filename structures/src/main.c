#include "tas.h"
#include <stdio.h>

int main(){	
	data_t tab[] = {14, 4, 5, 10, 11, 23, 6, 12, 20};

	tri_tas(&tab, 9);
	for(int i=0; i<9; i++){
		printf("%d\n", tab[i]);
	}
}