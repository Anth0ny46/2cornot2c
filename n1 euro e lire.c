#include<stdio.h>

#define CONVERTION 1936.36

#define EURO_2_LIRE(euro) (euro)*CONVERTION
#define LIRE_2_EURO(lire) (lire)/CONVERTION

int main(void){
	int scelta;
	double input_value;
	printf("1. EURO -> LIRE\n");
	printf("2. LIRE -> EURO\n");
	printf("\n");
	scanf("%d", &scelta);
	
	switch(scelta){
		case 1:
			printf("Inserisci il valore in euro da convertire:\n");
			scanf("%lf", &input_value);
			printf("%.3f (euro) -> %.3f (lire)\n", input_value, EURO_2_LIRE(input_value));
			break;
		case 2:
			printf("Inserisci il valore in lire da convertire:\n");
			scanf("%lf", &input_value);
			printf("%.3f (lire) -> %.3f (euro)\n", input_value, LIRE_2_EURO(input_value));
			break;
		default:
			printf("Operazione non riconosciuta\n");
	}
	return 0;
}

