#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arithmetique.h"

int main() {
	
	char *message, *messageDecode;
	int tailleOccur;
	occur_t *tableauOccurrences;
	intervalle_t *listeIntervalles;
	double messageCode;
	
	message = saisirMessage();
	tableauOccurrences = compterOccurrencesMessage(message, &tailleOccur);
	listeIntervalles = initialiserListeIntervalles(tableauOccurrences, strlen(message), tailleOccur);
	afficherListeIntervalles(listeIntervalles, strlen(message), tailleOccur);
	messageCode = coderMessage(listeIntervalles, message);
	printf("\nMessage codé : %.10lf\n", messageCode);
	messageDecode = decoderMessage(listeIntervalles, messageCode, strlen(message));
	printf("\nMessage décodé : %s\n", messageDecode);
	detruireMessage(message);
	detruireMessage(messageDecode);
	detruireOccurrences(tableauOccurrences);
	
	return 0;
}
