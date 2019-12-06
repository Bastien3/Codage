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
	int* sequencePolynomes1; /* Cette séquence de bits contient des 1 aux endroits où les termes du polynôme sont définis (exemple x^5 + x^4 + x^2 donne 11010) */
	int* sequencePolynomes2; /* Un polynôme différent pour chaque séquence */
	int* sequenceCodee1, *sequenceCodee2, *sequenceGold; /* Les séquences à longueur maximale générées */
	FFILE sequence;

	/* Définition de la longueur de la séquence et de la longueur maximale */
	printf("Saisir la longueur des séquences à générer : ");
	scanf("%d", &longueurSequence);
	nombreSequences = pow(2,longueurSequence) - 1;
	sequenceCodee1 = malloc(sizeof(int) * nombreSequences);
	sequenceCodee2 = malloc(sizeof(int) * nombreSequences);
	sequenceGold = malloc(sizeof(int) * nombreSequences); 

	/* Définition de la séquence d'initialisation */
	sequenceInitialisation = malloc(sizeof(int) * longueurSequence);
	do {
		printf("Saisir la séquence d'initialisation : ");
		sequenceSaisir(sequenceInitialisation, longueurSequence);
	} while (!sequenceVerifier(sequenceInitialisation, longueurSequence));

	/* Définition du polynôme 1 */
	sequencePolynomes1 = malloc(sizeof(int) * longueurSequence);
	do {
		printf("Saisir la séquence des polynômes de la séquence 1 (leur coefficient 1 ou 0) : ");
		sequenceSaisir(sequencePolynomes1, longueurSequence);
	} while (!sequenceVerifier(sequencePolynomes1, longueurSequence));
	sequenceInverser(sequencePolynomes1, longueurSequence); 
	
	/* Définition du polynôme 2 */
	sequencePolynomes2 = malloc(sizeof(int) * longueurSequence);
	do {
		printf("Saisir la séquence des polynômes de la séquence 1 (leur coefficient 1 ou 0) : ");
		sequenceSaisir(sequencePolynomes2, longueurSequence);
	} while (!sequenceVerifier(sequencePolynomes2, longueurSequence));
	sequenceInverser(sequencePolynomes2, longueurSequence); 

	/* Génération des séquences et des séquences à longueur maximale codées */
	sequence = FileCreer(longueurSequence + 1);
	longueurMaximaleGenerer(sequence, sequenceInitialisation, longueurSequence);
	printf("\nSéquence générée : ");
	FileAfficher(sequence);
	printf("\n\nListe des séquences générées pour la séquence 1 : ");
	listeSequencesGenerer(sequence, sequencePolynomes1, longueurSequence, sequenceCodee1, nombreSequences);
	printf("\nSéquence 1 codée : ");
	sequenceAfficher(sequenceCodee1, nombreSequences);
	printf("\nListe des séquences générées pour la séquence 2 : ");
	listeSequencesGenerer(sequence, sequencePolynomes2, longueurSequence, sequenceCodee2, nombreSequences);
	printf("\nSéquence 2 codée : ");
	sequenceAfficher(sequenceCodee2, nombreSequences);
	
	/* Génération de la séquence de Gold */
	for (int i = 0 ; i < nombreSequences ; i++)
		sequenceGold[i] = xor(sequenceCodee1[i], sequenceCodee2[i]);
	printf("\nSéquence de Gold : ");
	sequenceAfficher(sequenceGold, nombreSequences);
	
	/* Libération des zones mémoires allouées */
	FileDetruire(sequence);
	free(sequenceInitialisation);
	free(sequencePolynomes1);
	free(sequencePolynomes2);
	free(sequenceCodee1);
	free(sequenceCodee2);
	free(sequenceGold);
	 exit(0);
}
