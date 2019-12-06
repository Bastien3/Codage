#ifndef _ELTINT_H                   /* pour l'inclusion conditionnelle */
#define  _ELTINT_H

/* Déclaration d'un type concret ELEMENT
- un élément est dans ce fichier de type int ; par convention l'élément vide est 32767;
 le stockage est direct*/

/* plus généralement pour un stockage direct un élément de type simple ou "pas trop gros"
par exemple : un nombre complexe, un point */


/* Déclaration du type auxiliaire bool */
typedef enum {FAUX, VRAI} bool ;

/* Un élément est un entier, bit de la séquence */
typedef int ELEMENT;

#define ELEMENT_VIDE 32767

/* Déclaration des primitives du TDA ELEMENT */
void ElementAfficher(ELEMENT);
ELEMENT ElementAffecter(ELEMENT*, ELEMENT);
	/* affecte le deuxieme argument dans le premier
	qui est donc modifié et passé par adresse */
bool ElementIdentique(ELEMENT, ELEMENT);
	/* retourne vrai si les deux arguments sont identiques */

/* Primitives inutiles pour le stockage direct, Mais obligatoire en
   stockage indirect */

ELEMENT ElementCreer() ;
void ElementDetruire(ELEMENT) ;


#endif
