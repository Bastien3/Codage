#include "fonctionsCodage.h"
#include "filtabci.h"
#include <stdio.h>
#include <stdlib.h>

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

/* Crée la file circulaire contenant la séquence e longueur maximale de départ */
void longueurMaximaleGenerer(FFILE f, int* sequenceInitialisation, int tailleSequence) {

    int i;
    for (i = 0 ; i < tailleSequence ; i++)
        FileEntrer(sequenceInitialisation[i], f);
}

/* Génère la liste des séquences à longueur maximale et remplit la séquence codée par le dernier bit de chaque séquence */
void listeSequencesGenerer(FFILE f, int* sequencePolynomes, int tailleSequence, int *sequenceCodee, int nombreSequences) {

        int i, j;
        int* sequence = malloc(sizeof(int) * tailleSequence);
        int bitAAjouter = 0; /* Bit à ajouter au début de la séquence */

        for (i = 0 ; i < nombreSequences ; i++) {
            printf("\n");
            FileAfficher(f);
            for (j = 0 ; j < tailleSequence ; j++)
                if (sequencePolynomes[j]) { /* Calcul du bit à ajouter au début de la séquence */
                    printf(" [%d %d]", j, f->elements[j]);
                    bitAAjouter = xor(bitAAjouter, f->elements[j]);
                }
            printf(" -> %d\n", bitAAjouter);
            sequenceCodee[i] = FileSortir(f);
            FileEntrer(bitAAjouter, f);
            bitAAjouter = 0;
        }
        printf("\n");
}
