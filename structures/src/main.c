#include "tas.h"


int main(){	
	tas_t tas;

	init_tas(10, &tas);
	inserer_tas(&tas, 10);
	inserer_tas(&tas, 11);
	inserer_tas(&tas, 1);

	liberer_tas(&tas);
}