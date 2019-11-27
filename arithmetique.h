#ifndef _ARITHMETIQUE_H_
#define _ARITHMETIQUE_H_

#include <stdbool.h>

/* Structures à adopter pour le (dé)codage arithmétique */
typedef struct {
	char carac;
	int occurrence;
	bool connu;
} occur_t;

typedef struct {
	occur_t *carac;
	double debut;
	double fin;
} intervalle_t;

typedef struct {
	double gauche;
	double droit;
} intervalleCode_t;

/*
 *	Etape 1 : On calcule les occurrences des caractères du mot reçu
 */

/* Saisie du message à coder/décoder - allocation dynamique de la mémoire */
char * saisirMessage();

/* Libération de la mémoire du message */
void detruireMessage(char *mot);

/* Tranforme tous les caractères minuscules du message en majuscules */
void enMajuscules (char* message);

/* Création et initialisation du tableau des occurrences */
occur_t * creerTableauOccurrences(int tailleMsg);

/* Compte le nombre d'occurrences des caractères d'un message */
/* tailleOccur : taille du tableau d'occurrences calculée par la fonction */
occur_t * compterOccurrencesMessage(char * msg, int *tailleOccur);

/* Affichage du tableau des occurrences */
void afficherTableauOccurrences(occur_t *repets, int tailleMsg);

/* Destruction d'une structure d'occurrences */
void detruireOccurrences(occur_t * liste);



/*
 *	Etape 2 : On calcule les probabilités d'apparition des caractères dans le mot
 */

/* Création de la liste des intervalles */
intervalle_t * creerListeIntervalles(occur_t *repets, int tailleTabOccurrences);

/* Initialisation de la liste des intervalles */
intervalle_t * initialiserListeIntervalles(occur_t *repets, int tailleMsg, int tailleOccur);

/* Affichage de la liste des intervalles */
void afficherListeIntervalles(intervalle_t *intervs, int tailleMsg, int tailleOccur);

/* Destruction d'une structure d'intervalles */
void detruireIntervalles(intervalle_t *liste);



/*
 *	Etape 3 : On code le mot avec la probabilité totale d'apparition de ses caractères
 */

/* Codage du message grâce à la liste des intervalles (renvoi d'une probabilité d'apparition du caractère) */
intervalleCode_t coderMessage(intervalle_t *liste, char* message);



/*
 *	Etape 4 : On décode le mot avec la probabilité totale d'apparition de ses caractères
 */

// à compléter
//char * decoderMessage(float probabilite);

#endif
