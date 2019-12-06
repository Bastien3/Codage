#include <stdio.h>
#include <stdlib.h>

#define N 8
#define TAILLE_MESSAGE 3
#define TAILLE_MESSAGE_ETALE TAILLE_MESSAGE * N

/* Fonction calculant la séquence d'étalement du message passé en paramètre en fonction de la matrice de Hadamard générée */
/* Paramètres : 
 * sequenceHadamard : la séquence d'Hadamard choisie par l'utilisateur dans la matrice de Hadamard
 * messageUtilisateur : le message à étaler
*/
int *etalerMessage(int sequenceHadamard[N], int *messageUtilisateur) {

	int i, j;
	int *messageEtale = malloc(sizeof(int) * (TAILLE_MESSAGE_ETALE + 1)); /* Création du message étalé */
	int message[TAILLE_MESSAGE];

	/* Remplacement des 0 par des -1 dans le message utilisateur */	
	for (i = 0 ; i < TAILLE_MESSAGE ; i++)
		message[i] = messageUtilisateur[i] == 0 ? -1 : 1;

	/* Génération du message étalé */
	/* Parcours des bits du message */
	for (i = 0 ; i < TAILLE_MESSAGE ; i++)
		/* Parcours des bits du message étalé (séquences de N bits) */
		for (j = i * N ; j < (i + 1) * N ; j++)	{
			/* Produit entre le bit du message et chacun des N bits de la séquence issue de la matrice de Hadamard */
			messageEtale[j] = sequenceHadamard[j % N] * message[i];
		}

	return messageEtale;
}

/* Calcule la somme des messages étalés des utilisateurs (signal étalé) */
/* Paramètre : la matrice des messages étalés */
int *operationEtalement(int **messagesEtales) {

	int i, j, somme = 0;
	int *sommeMessages = malloc(sizeof(int) * TAILLE_MESSAGE_ETALE);

	/* Création de la somme des message étalés */
	/* Parcours de chacun des bits d'étalement */
	for (j = 0 ; j < TAILLE_MESSAGE_ETALE ; j++) {
		/* Parcours du j-ième bit de chacun des messages étalés */
		for (i = 0 ; i < N ; i++)
			somme += messagesEtales[i][j];
		sommeMessages[j] = somme;
		somme = 0;
	}
	
	return sommeMessages;
}

/* Génération deu message original à partir du signal étalé et de la séquence de Hadamard correspondante */
/* Paramètres : 
 * sequenceHadamard : la séquence d'Hadamard choisie par l'utilisateur dans la matrice de Hadamard
 * sommeMessages : le signal étalé issu de la somme des messages étalés
*/
int *desetalerMessage(int sequenceHadamard[N], int *sommeMessages) {

	int i, j;
	int somme = 0;
	int *messageDesetale = malloc(sizeof(int) * TAILLE_MESSAGE);

	/* Création du message désétalé */
	/* Pour chacun des bits à décoder */
	for (i = 0 ; i < TAILLE_MESSAGE ; i++) {
		/* Parcours de la partie du message étalé correspondant à ce bit */
		for (j = i * N ; j < (i + 1) * N ; j++)
			somme += sequenceHadamard[j % N] * sommeMessages[j]; /* Somme des valeurs de cette partie */
		messageDesetale[i] = (somme >= N / 2); /* S'il y a eu des erreurs, le bit décodé correspond à 1 si la somme est plus proche de N que de 0, à 0 sinon */
		somme = 0;
	}
	
	return messageDesetale;
} 

/* Affichage d'un tableau, sert à contrôler les résultats */
void afficherTableau(int *tableau, int tailleTableau) {

	int i;

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
	int messagesUtilisateur[N][TAILLE_MESSAGE + 1] = { /* Dernier chiffre du message : numéro de séquence choisi */
													{0,0,0,0},
													{0,0,1,2},
													{0,1,0,4},
													{0,1,1,6},
													{1,0,0,1},
													{1,0,1,3},
													{1,1,0,5},
													{1,1,1,7},
													}; 
	int sequence[N]; /* Contient la séquence à utiliser pour l'étalement */
	int numeroSequence; /* Numéro de séquence dans la matrice de Hadamard */
	int *messagesEtales[N]; /* Liste des messages après étalement */
	int *messagesDesetales[N]; /* Liste des messages après désétalement */
	int *sommeMessages; /* Contient le signal étalé */

	/* Affichage des messages des utilisateurs */
	for (i = 0 ; i < N ; i++) {
		printf("Utilisateur %d : message : ", i);
		afficherTableau(messagesUtilisateur[i], TAILLE_MESSAGE);
	}
	printf("\n");

	/* Création des messages étalés */
	for (i = 0 ; i < N ; i++) {
		numeroSequence = messagesUtilisateur[i][TAILLE_MESSAGE];
		for (j = 0 ; j < N ; j++)
			sequence[j] = matriceHadamard[numeroSequence][j]; /* Génération de la séquence */
		messagesEtales[i] = etalerMessage(sequence, messagesUtilisateur[i]);
		printf("Utilisateur %d : message étalé : ", i);
		afficherTableau(messagesEtales[i], TAILLE_MESSAGE_ETALE);
	}
	printf("\n");

	/* Génération du signal */
	sommeMessages = operationEtalement(messagesEtales);
	printf("Signal étalé : ");
	afficherTableau(sommeMessages, TAILLE_MESSAGE_ETALE);
	printf("\n");

	/* Création des messages désétalés */
	for (i = 0 ; i < N ; i++) {
		numeroSequence = messagesUtilisateur[i][TAILLE_MESSAGE];
		for (j = 0 ; j < N ; j++)
			sequence[j] = matriceHadamard[numeroSequence][j]; /* Génération de la séquence */
		messagesDesetales[i] = desetalerMessage(sequence, messagesEtales[i]);
		printf("Utilisateur %d : message désétalé : ", i);
		afficherTableau(messagesDesetales[i], TAILLE_MESSAGE);
	}
	printf("\n");
		
	return 0;	

}
