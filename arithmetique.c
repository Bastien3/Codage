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
	printf("\n\nTri bulle...\n\n");
	
	/* Tri bulle alphabétique des caractères */
  	int passage = 0;
    bool permutation = true;
    int en_cours;
       
    while (permutation) {
        permutation = false;
        passage++;
        for (en_cours = 0 ; en_cours < *tailleOccur - passage ; en_cours++) {
            if (repets[en_cours].carac > repets[en_cours + 1].carac) {
                permutation = true;
                // on echange les deux elements
                temp = repets[en_cours];
                repets[en_cours] = repets[en_cours + 1];
                repets[en_cours + 1] = temp;
            }
        }
    }


	afficherTableauOccurrences(repets, *tailleOccur);
	repets = realloc(repets, sizeof(occur_t) * tailleMsg);
	return repets;
}

/* Affichage du tableau des occurrences */
void afficherTableauOccurrences(occur_t *repets, int tailleMsg) {
	
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
	
	/* On remplit les informations concernant le caractère étudié (lettre, nombre d'occurences) pour chaque intervalle */
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
	
	for (i = 0 ; i < tailleOccur ; i++) {
		liste[i].debut = valeur;
		valeur += (double)liste[i].carac->occurrence / tailleMsg;
		liste[i].fin = valeur;
	} 
	
	return liste;
}

/* Affichage de la liste des intervalles */
void afficherListeIntervalles(intervalle_t *intervs, int tailleMsg, int tailleOccur) {

	for(int i = 0; i < tailleOccur; i++)
		if(intervs[i].carac->occurrence > 0) {
			printf("Caractère \"%c\"\n", intervs[i].carac->carac);
			printf("\tFréquence d'apparition = (%i/%i)\n", intervs[i].carac->occurrence, tailleMsg);
			printf("\tIntervalle : [%lf ; %lf[\n\n", intervs[i].debut, intervs[i].fin);
		}
	printf("\n");
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
intervalleCode_t coderMessage(intervalle_t *liste, char* message) {

	intervalleCode_t intervalleCode;
	double intervalleReference = 1;
	intervalle_t intervalle;
	int i, j;
	
	for (j = 0 ; liste[j].carac->carac != message[i] ; j++); /* Recherche de l'intervalle correspondant au caractère courant */
	intervalle = liste[j];
	intervalleCode.gauche = intervalle.debut; /* Initialisation de la borne gauche */
	intervalleCode.droit = intervalle.fin; /* Initialisation de la borne droite */
		
	for (i = 1 ; message[i] ; i++) {
		intervalleReference /= sizeof(message);
		for (j = 0 ; liste[j].carac->carac != message[i] ; j++); /* Recherche de l'intervalle correspondant au caractère courant */
		intervalle = liste[j];
		intervalleCode.droit = intervalleCode.gauche;
		intervalleCode.gauche += intervalleReference * intervalle.debut; /* Mise à jour de la borne gauche */
		intervalleCode.droit += intervalleReference * intervalle.fin; /* Mise à jour de la borne droite */
		printf("Référence : %.10lf, borne gauche : %.10lf, borne droite : %.10lf\n", intervalleReference, intervalleCode.gauche, intervalleCode.droit);
		printf("Caractère : %c, début : %lf, fin : %lf\n", intervalle.carac->carac, intervalle.debut, intervalle.fin);
	}
	
	return intervalleCode;
}


/* Décodage du mot en fonction de l'intervalle envoyé en paramètre */
/* Complexité O(n²) */
char *decoderMessage(intervalle_t *liste, char* message, intervalleCode_t intervalleCode) {

	double borneGauche, borneDroite;
	double intervalleReference = 1;
	intervalle_t intervalle;
	int i, j;
	
	for (j = 0 ; liste[j].carac->carac != message[i] ; j++); /* Recherche de l'intervalle correspondant au caractère courant */
	intervalle = liste[j];
	borneGauche = intervalle.debut; /* Initialisation de la borne gauche */
	borneDroite = intervalle.fin; /* Initialisation de la borne droite */
		
	for (i = 1 ; message[i] ; i++) {
		intervalleReference /= sizeof(message);
		for (j = 0 ; liste[j].carac->carac != message[i] ; j++); /* Recherche de l'intervalle correspondant au caractère courant */
		intervalle = liste[j];
		borneDroite = borneGauche;
		borneGauche += intervalleReference * intervalle.debut; /* Mise à jour de la borne gauche */
		borneDroite += intervalleReference * intervalle.fin; /* Mise à jour de la borne droite */
		printf("Référence : %.10lf, borne gauche : %.10lf, borne droite : %.10lf\n", intervalleReference, borneGauche, borneDroite);
		printf("Caractère : %c, début : %lf, fin : %lf\n", intervalle.carac->carac, intervalle.debut, intervalle.fin);
	}
	
	return "xxx";
}

