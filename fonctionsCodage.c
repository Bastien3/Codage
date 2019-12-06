#include "fonctionsCodage.h"
#include "filtabci.h"
#include <stdio.h>

/* Calcule un xor entre 2 bits */
int xor(int a, int b) {
    return (a + b) % 2;
}

/* Permet de saisir une séquence */
void sequenceSaisir(int *sequence, int tailleSequence) {

    int i;
    for (i = 0 ; i < tailleSequence ; i++)
        scanf("%d", &sequence[i]);
}

/* Vérifie que la séquence est faite de 0 et de 1 */
int sequenceVerifier(int *sequence, int tailleSequence) {

    int i;
    for (i = 0 ; i < tailleSequence ; i++)
        if (sequence[i] < 0 || sequence[i] > 1)
            return 0;
    return 1;
}

/* Affiche une séquence */
void sequenceAfficher(int *sequence, int tailleSequence) {

    int i;
    for (i = 0 ; i < tailleSequence ; i++)
        printf("%d ", sequence[i]);
    printf("\n");
}

/* Permet d'inverser une séquence */
void sequenceInverser(int *sequence, int tailleSequence) {

    int i, j, temp;
    for (i = 0, j = tailleSequence - 1 ; i < j ; i++, j--) {
    	temp = sequence[i];
    	sequence[i] = sequence[j];
    	sequence[j] = temp;
    }
}

/* Crée la file circulaire contenant la séquence de longueur maximale de départ */
void longueurMaximaleGenerer(FFILE f, int* sequenceInitialisation, int tailleSequence) {

    int i;
    for (i = 0 ; i < tailleSequence ; i++)
        FileEntrer(sequenceInitialisation[i], f);
}

/* Génère la liste des séquences à longueur maximale et remplit la séquence codée par le dernier bit de chaque séquence */
void listeSequencesGenerer(FFILE f, int* sequencePolynomes, int tailleSequence, int *sequenceCodee, int nombreSequences) {

        int i, j;
        int bitAAjouter = 0; /* Bit à ajouter au début de la séquence */

        for (i = 0 ; i < nombreSequences ; i++) {
        	/* On affiche la séquence qu'on vient de générer */
            printf("\n");
            FileAfficher(f);
            for (j = 0 ; j < tailleSequence ; j++) /* Calcul du bit à ajouter au début de la séquence */
                if (sequencePolynomes[j]) /* On fait un XOR entre les bits qui sont à considérer d'après le polynôme */
                    bitAAjouter = xor(bitAAjouter, f->elements[(j + f->debut) % f->longMax]);
            /* On décale la séquence actuelle pour y ajouter le bit calculé */
            sequenceCodee[i] = FileSortir(f);
            FileEntrer(bitAAjouter, f);
            bitAAjouter = 0;
        }
        printf("\n");
}
