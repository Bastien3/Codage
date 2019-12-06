/* Implantation du TDA FILE par tableau circulaire

    Un objet file est un pointeur sur une structure qui contient
    * l'indice courant du début de la file
    * l'indice courant de la fin de la file
    * la taille maximale de la file, spécifiée par la primitive de création de pile
    * un pointeur vers une zone de taille : longMax*(sizeof(ELEMENT)) octets
    qui contient les éléments de la file

    Une file est vide ssi debut = fin + 1 modulo longMax
    Une file est pleine ssi debut = fin + 2 modulo longMax

*/

#include "filtabci.h"
#include <stdlib.h>
#include <stdio.h>

 FFILE FileCreer (int profondeur)	{
 /* renvoie l'adresse d'une structure dont le champ éléments est un pointeur sur une
 zone mémoire de profondeur*taille(ELEMENT) */
	FFILE p;

	p=(FFILE)malloc(sizeof(file));
	if (! p) {
		printf("pb de mémoire") ;
		exit(0) ;
                }
 	p->elements=(ELEMENT *)malloc(profondeur*sizeof(ELEMENT)) ;
	p->debut= 0	;
        p->fin = profondeur - 1 ;
 	p->longMax= profondeur	;

 	return(p);
 }

 int FileVide(FFILE P)	{
	return(P->debut== (P->fin +1)% P->longMax);
 }

 /* utilitaire FilePleine */
 int FilePleine (FFILE P)	{
	return (P->debut== (P->fin +2) % P->longMax);
 }

 ELEMENT FileSortir(FFILE P)	{
	ELEMENT elt  ;
	if (!FileVide(P)) 	{
		ElementAffecter( &elt, (P->elements)[P->debut]);
		P->debut = (P->debut + 1) % P->longMax;
 		return(elt);
 	}
	else return (ElementCreer());
 }

int FileEntrer(ELEMENT elt, FFILE P)	{
 	if(! FilePleine( P))	{
		 P->fin = (P->fin + 1) % P->longMax;
		ElementAffecter( &(P->elements)[P->fin], elt);
 		return(1);
 	}
 	else {
		printf("FFILE pleine\n");
 		return(0);
 	}
 }

 ELEMENT FileDebut(FFILE P)	{
	if (! FileVide(P))
		return( (P->elements)[P->debut] );
		else return (ElementCreer()) ;
 }

 void FileDetruire(FFILE P)	{
 	free(P->elements);
 	free(P);
 }

 void FileAfficher (FFILE P) {
	int i ;
	if (! FileVide(P)) {
		if (P->debut <= P->fin) {
			for (i = P-> debut ; i <= P -> fin; i ++ )
				ElementAfficher(P -> elements [i]) ;
        } else {
		    for (i = P-> debut ; i <= (P -> fin + P->longMax); i++  )
			    ElementAfficher(P -> elements [i% P->longMax]) ;
        }
    }
}

void FileRadiographier(FFILE P) {
	int i ;
	printf("\n debut : %d  , fin : %d", P->debut, P->fin) ;
	for (i = 0 ; i <= P -> longMax -1 ; i++)  {
		printf("\n indice : %d , element : ",i) ;
		ElementAfficher(P -> elements [i]) ;
		}
}
