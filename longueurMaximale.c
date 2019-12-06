#include "filtabci.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fonctionsCodage.h"

int main()
{
	int longueurSequence; /* Longueur de la séquence de départ */
	int nombreSequences; /* Nombre de séquences générées par l'algorithme */
	int* sequenceInitialisation; /* Séquence de départ */
	int* sequencePolynomes; /* Cette séquence de bits contient des 1 aux endroits où les termes du polynôme sont définis (exemple x^5 + x^4 + x^2 donne 11010) */
	int* sequenceCodee; /* La séquence à longueur maximale générée */
	FFILE sequence; /* Une file circulaire qui contient chacune des séquences générées */

	/* Définition de la longueur de la séquence et de la longueur maximale */
	printf("Saisir la longueur de la séquence à générer : ");
	scanf("%d", &longueurSequence);
	nombreSequences = pow(2,longueurSequence) - 1;
	sequenceCodee = malloc(sizeof(int) * nombreSequences);

	/* Définition de la séquence d'initialisation */
	sequenceInitialisation = malloc(sizeof(int) * longueurSequence);
	do {
		printf("Saisir la séquence d'initialisation : ");
		sequenceSaisir(sequenceInitialisation, longueurSequence);
	} while (!sequenceVerifier(sequenceInitialisation, longueurSequence));

	/* Définition du polynôme */
	sequencePolynomes = malloc(sizeof(int) * longueurSequence);
	do {
		printf("Saisir la séquence des polynômes (leur coefficient 1 ou 0) : ");
		sequenceSaisir(sequencePolynomes, longueurSequence);
	} while (!sequenceVerifier(sequencePolynomes, longueurSequence));
	/* on inverse la séquence car la file circulaire entre les bits à la fin et les sort au début (censée faire l'inverse) */
	sequenceInverser(sequencePolynomes, longueurSequence); 

	/* Génération des séquences */
	sequence = FileCreer(longueurSequence + 1);
	longueurMaximaleGenerer(sequence, sequenceInitialisation, longueurSequence);
	printf("\n\nSéquence générée : ");
	FileAfficher(sequence);
	printf("\n\nListe des séquences générées : ");
	listeSequencesGenerer(sequence, sequencePolynomes, longueurSequence, sequenceCodee, nombreSequences);
	
	/* Génération de la séquence codée */
	printf("\n\nSéquence codée : ");
	sequenceAfficher(sequenceCodee, nombreSequences);
	
	/* Libération des zones mémoires allouées */
	FileDetruire(sequence);
	free(sequenceInitialisation);
	free(sequencePolynomes);
	free(sequenceCodee);
	exit(0);
}
