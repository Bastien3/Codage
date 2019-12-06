/* Permet de saisir une séquence */
#ifndef FONCTIONS_CODAGE
#define FONCTIONS_CODAGE
#include "filtabci.h"

/* Calcule un xor entre 2 bits */
int xor(int a, int b);

/* Permet de saisir une séquence */
void sequenceSaisir(int *sequence, int tailleSequence);

/* Vérifie que la séquence est faite de 0 et de 1 */
int sequenceVerifier(int *sequence, int tailleSequence);

/* Affiche une séquence */
void sequenceAfficher(int *sequence, int tailleSequence);

/* Extrait une séquence de la file de longueur maximale */
void sequenceExtraire(FFILE f, int *sequence, int tailleSequence);

/* Permet d'inverser une séquence */
void sequenceInverser(int *sequence, int tailleSequence);

/* Crée la file circulaire contenant la séquence e longueur maximale de départ */
void longueurMaximaleGenerer(FFILE f, int* sequenceInitialisation, int tailleSequence);

/* Génère la liste des séquences à longueur maximale et remplit la séquence codée par le dernier bit de chaque séquence */
void listeSequencesGenerer(FFILE f, int* sequencePolynomes, int tailleSequence, int *sequenceCodee, int nombreSequences);

#endif
