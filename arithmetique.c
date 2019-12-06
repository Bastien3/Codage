#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arithmetique.h" // Importation des prototypes de fonctions

/*******************		ETAPE 1			 *******************/
/* Calcul du nombre d'occurrences de chaque lettre du message */

/* Saisie du message à coder/décoder - allocation dynamique de la mémoire */
char * saisirMessage() {

	char *phrase = malloc(sizeof(char*));
	
	printf("Entrez votre message  : ");
	scanf("%s", phrase);
	
	return phrase;
}

/* Libération de la mémoire du message */
void detruireMessage(char *mot) {
	free(mot);	
}

/* Tranforme tous les caractères minuscules du message en majuscules */
void enMajuscules (char* message) {

	int i;
	for (i = 0 ; message[i] ; i++)
		if (message[i] >= 'a' && message[i] <= 'z')
			message[i] = message[i] - ('a' - 'A');
}

/* Création et initialisation du tableau des occurrences */
occur_t * creerTableauOccurrences(int tailleMsg) {

	occur_t *intervs = malloc(tailleMsg * sizeof(occur_t));
	
	for(int i = 0; i < tailleMsg; i++) {
		intervs[i].carac = '*';
		intervs[i].occurrence = 0;
		intervs[i].connu = false;
	}
	
	return intervs;
}

/* Compte le nombre d'occurrences des caractères d'un message */
/* tailleOccur : taille du tableau d'occurrences calculée par la fonction */
/* Complexité O(n²) */
occur_t * compterOccurrencesMessage(char * msg, int *tailleOccur) {

	int i, j, tailleMsg = strlen(msg);
	occur_t *repets = creerTableauOccurrences(tailleMsg), temp;
	*tailleOccur = 0;
	
	enMajuscules(msg);
	
	printf("\nEtablissement du tableau de statistiques d'apparition de chaque lettre dans le mot.\n");
	
	/* Comptage des occurrences */
	/* On parcourt chaque lettre du message */
	for (i = 0 ; i < tailleMsg ; i++) {
		/* Pour chacune de ces lettres, soit on l'ajoute au tableau d'occurrences, soit on incrémente son nombre d'occurrences */
		for (j = 0; j <= i; j++) {
			if (repets[j].connu == false) {
				repets[j].carac = msg[i];
				repets[j].occurrence = 1; /* Première occurrence */
				repets[j].connu = true; /* Caractère maintenant connu */
				(*tailleOccur)++; /* Comptage du nombre de caractères dans le tableau des occurrences */
				j = i; /* Comme on a incrémenté l'occurrence du caractère courant, inutile de continuer à parcourir le tableau des occurrences */
			} else
				/* On incrémente le nombre d'occurrences des caractères déjà reconnus */
				if(repets[j].carac == msg[i]) {
					repets[j].occurrence++;
					j = i; 
				}
		}
	}
	
	afficherTableauOccurrences(repets, *tailleOccur);
	repets = realloc(repets, sizeof(occur_t) * tailleMsg);
	return repets;
}

/* Affichage du tableau des occurrences */
void afficherTableauOccurrences(occur_t *repets, int tailleMsg) {
	
	printf("\n");
	for(int i = 0; i < tailleMsg; i++)
		printf("Caractère \"%c\" identifié %i fois\n", repets[i].carac, repets[i].occurrence);
	printf("\n");
}

/* Destruction d'une structure d'occurrences */
void detruireOccurrences(occur_t * liste) {
	free(liste);
}


/*******************		ETAPE 2			 *******************/
/* Création de la liste d'intervalles correspondant à la proportion d'apparitions des lettres dans le message */

/* Création de la liste des intervalles */
intervalle_t * creerListeIntervalles(occur_t *repets, int tailleTabOccurrences) {

	int i;	
	intervalle_t *tab = malloc(tailleTabOccurrences * sizeof(intervalle_t));
	
	/* On remplit les informations concernant le caractère étudié (lettre, nombre d'occurrences) pour chaque intervalle */
	/* Les intervalles ne sont pas encore calculés */
	for(i = 0; i < tailleTabOccurrences; i++) {
			tab[i].carac = malloc(sizeof(occur_t));
			tab[i].carac = &repets[i];
		}
		
	return tab;
}

/* Initialisation de la liste des intervalles */
intervalle_t * initialiserListeIntervalles(occur_t *repets, int tailleMsg, int tailleOccur) {

	intervalle_t *liste = creerListeIntervalles(repets,tailleMsg);
	double valeur = 0;
	int i;
	
	printf("Création du tableau d'intervalles de chaque lettre du mot.\n");
	
	for (i = 0 ; i < tailleOccur ; i++) {
		liste[i].debut = valeur;
		valeur += (double)liste[i].carac->occurrence / tailleMsg;
		liste[i].fin = valeur;
	} 
	
	return liste;
}

/* Affichage de la liste des intervalles */
void afficherListeIntervalles(intervalle_t *intervs, int tailleMsg, int tailleOccur) {

	int i;
	printf("\n");
	for(i = 0; i < tailleOccur; i++) {
		printf("Caractère \"%c\"\n", intervs[i].carac->carac);
		printf("\tFréquence d'apparition = (%i/%i)\n", intervs[i].carac->occurrence, tailleMsg);
		printf("\tIntervalle : [%lf ; %lf[\n\n", intervs[i].debut, intervs[i].fin);
	}
}

/* Destruction d'une structure d'intervalles */
void detruireIntervalles(intervalle_t * liste) {
	liste->carac = NULL;
	free(liste->carac);
	free(liste);
}


/*******************		ETAPE 3			 *******************/

/* Calcul de l'intervalle issu du code arithmétique */
/* Le mot codé est la borne gauche */
/* Complexité O(n²) */
double coderMessage(intervalle_t *liste, char* message) {

	intervalleCode_t intervalleCode; /* L'intervalle de codage */
	double difference; /* La référence par laquelle multiplier chaque borne de l'intervalle */
	intervalle_t intervalle; /* Un intervalle temporaire */
	int i, j;
	
	intervalleCode.gauche = 0;
	intervalleCode.droit = 1;
	
	for (i = 0 ; message[i] ; i++) {
		difference = intervalleCode.droit - intervalleCode.gauche;
		for (j = 0 ; liste[j].carac->carac != message[i] ; j++); /* Recherche de l'intervalle correspondant au caractère courant */
		intervalle = liste[j];
		intervalleCode.droit = intervalleCode.gauche + difference * intervalle.fin; /* Mise à jour de la borne droite */
		intervalleCode.gauche += difference * intervalle.debut; /* Mise à jour de la borne gauche */
	}
	
	return (intervalleCode.droit + intervalleCode.gauche) / 2;
}


/* Décodage du mot en fonction de l'intervalle envoyé en paramètre */
/* Complexité O(n²) */
char *decoderMessage(intervalle_t *liste, double messageCode, int tailleMessage) {

	int i, j;
	char *message = malloc(sizeof(char) * tailleMessage); 
	double probabilite; /* Probabilité d'apparition du caractère courant */
	double borneInferieure; /* Borne inférieure du caractère courant dans le tableau d'intervalles */
	
	for (i = 0 ; i < tailleMessage ; i++) {
		for (j = 0 ; messageCode < liste[j].debut || messageCode > liste[j].fin ; j++);  /* Recherche de l'intervalle dans lequel est le mot codé */
		message[i] = liste[j].carac->carac; /* Ajout du caractère correspondant au message */
		probabilite = (double)liste[j].carac->occurrence / tailleMessage;
		borneInferieure = liste[j].debut;
		messageCode = (messageCode - borneInferieure) / probabilite; /* Actualisation du nombre codé */	
	}
	
	return message;
}

