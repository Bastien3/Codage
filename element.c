/* définition des primitives du type concret ELEMENT entier */

#include "element.h"
#include <stdio.h>
#include <stdlib.h>

void ElementLire(ELEMENT * i)	{
	scanf("%d",i);
}

void ElementAfficher(ELEMENT elt)	{
	printf("%d  ",elt);
}

ELEMENT ElementAffecter(ELEMENT * e1, ELEMENT e2)   {
	return  *e1 = e2  ;
}

bool ElementIdentique(ELEMENT e1, ELEMENT e2)  {
	/* retourne vrai si les deux arguments sont identiques */
	return 	e1 == e2 ;
}

/* INUTILE Mais cohérent pour le stockage indirect */
ELEMENT ElementCreer()	{
	return ELEMENT_VIDE;
}

void ElementDetruire(ELEMENT x) 	{
}
