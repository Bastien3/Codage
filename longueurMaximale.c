#include "filtabci.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fonctionsCodage.h"

int main()
{
	int longueurSequence, nombreSequences;
	int* sequenceInitialisation = malloc(sizeof(int) * longueurSequence);
	int* sequencePolynomes = malloc(sizeof(int) * longueurSequence);
	int* sequenceCodee;
	FFILE sequence;

	printf("Saisir la longueur de la séquence à générer : ");
	scanf("%d", &longueurSequence);
	nombreSequences = pow(2,longueurSequence);
	sequenceCodee = malloc(sizeof(int) * nombreSequences);

	do {
		printf("Saisir la séquence d'initialisation : ");
		sequenceSaisir(sequenceInitialisation, longueurSequence);
	} while (!sequenceVerifier(sequenceInitialisation, longueurSequence));

	do {
		printf("Saisir la séquence des polynômes (leur coefficient 1 ou 0) : ");
		sequenceSaisir(sequencePolynomes, longueurSequence);
	} while (!sequenceVerifier(sequencePolynomes, longueurSequence));

	sequence = FileCreer(longueurSequence + 1);
	longueurMaximaleGenerer(sequence, sequenceInitialisation, longueurSequence);
	printf("\n\nSéquence générée : ");
	FileAfficher(sequence);
	printf("\n\nListe des séquences générées : ");
	listeSequencesGenerer(sequence, sequencePolynomes, longueurSequence, sequenceCodee, nombreSequences);
	FileDetruire(sequence);
	free(sequenceInitialisation);
	free(sequencePolynomes);
	free(sequenceCodee);
	 exit(0);
}
