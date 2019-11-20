#include <stdio.h>
#include <stdlib.h>

#define N 8

/* Fonction calculant la séquence d'étalement du message passé en paramètre en fonction de la matrice de Hadamard générée */

int * sequenceEtalement(int sequenceHadamard[N], int *messageUtilisateur) {

	int i, j;
	int tailleMessage; 
	int *messageCode = malloc(sizeof(int) * (tailleMessage * N + 1)); /* Création du message codé */

	/* Taille du message utilisateur */
	for (tailleMessage = 0 ; messageUtilisateur[tailleMessage] >= 0 ; tailleMessage++);
	/* Remplacement des 0 par des -1 dans le message utilisateur */

	int message[tailleMessage];
	for (i = 0 ; i < tailleMessage ; i++)
		message[i] = messageUtilisateur[i] == 0 ? -1 : 1;


	/* Génération du message étalé */
	/* Parcours des bits du message */
	for (i = 0 ; i < tailleMessage ; i++)
		/* Parcours des bits du message codé (séquences de N bits) */
		for (j = i * N ; j < (i + 1) * N ; j++)	{
			/* Produit entre le bit du message et chacun des N bits de la séquence issue de la matrice de Hadamard */
			messageCode[j] = sequenceHadamard[j % N] * message[i];
		}

	messageCode[j] = 0; /* Sentinelle */
	return messageCode;
}

//void operationEtalement (int matrice[
void afficherTableau(int *tableau) {

	int i;
	int tailleTableau;
	for (tailleTableau = 0 ; tableau[tailleTableau] != 0 ; tailleTableau++);

	for (i = 0 ; i < tailleTableau ; i++) {
		if (i % 4 == 0)
			printf("  ");
		printf("%d ", tableau[i]);
	}
	printf("\n");
}

int main() {

	int i, j;
	int matriceHadamard[N][N] = {
		{1,1,1,1,1,1,1,1},
		{1,-1,1,-1,1,-1,1,-1},
		{1,1,-1,-1,1,1,-1,-1},
		{1,-1,-1,1,1,-1,-1,1},
		{1,1,1,1,-1,-1,-1,-1},
		{1,-1,1,-1,-1,1,-1,1},
		{1,1,-1,-1,-1,-1,1,1},
		{1,-1,-1,1,-1,1,1,-1}
	};
	int messageUtilisateur[2][4] = {{1,0,1,-1},{0,1,1,-3}}; /* Sentinelle : nombre négatif, nombre opposé du numéro de séquence choisi */
	int sequence[N];
	int numeroSequence;
	int *messageCode;

	for (i = 0 ; i < 2 ; i++) {
		numeroSequence = -messageUtilisateur[i][3];
		for (j = 0 ; j < N ; j++)
			sequence[j] = matriceHadamard[numeroSequence][j]; /* Génération de la séquence */
		messageCode = sequenceEtalement(sequence, messageUtilisateur[i]);
		afficherTableau(messageCode);
		free(messageCode);
	}
	return 0;	

}
