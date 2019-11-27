#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arithmetique.h"

int main() {
	
	char *message;
	int tailleOccur;
	occur_t *tableauOccurrences;
	intervalle_t *listeIntervalles;
	intervalleCode_t intervalleCode;
	
	message = saisirMessage();
	printf("%s\n", message);
	tableauOccurrences = compterOccurrencesMessage(message, &tailleOccur);
	listeIntervalles = initialiserListeIntervalles(tableauOccurrences, sizeof(message), tailleOccur);
	afficherListeIntervalles(listeIntervalles, sizeof(message), tailleOccur);
	intervalleCode = coderMessage(listeIntervalles, message);
	printf("Message codé : %.10lf\n", intervalleCode.gauche);
	detruireMessage(message);
	detruireOccurrences(tableauOccurrences);
	
	return 0;
}
