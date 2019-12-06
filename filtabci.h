
/* Réalisation du TDA FILE par tableau circulaire

    Un objet file est un pointeur sur une structure qui contient
    * l'indice courant du début de la file
    * l'indice courant de la fin de la file
    * la taille maximale de la file, spécifiée par la primitive de création de pile
    * un pointeur vers une zone de taille : taille maximum *(sizeof(ELEMENT)) octets
    qui contient les éléments de la file

*/
#ifndef FILTABCI_H
#define FILTABCI_H

#include "element.h" 			/* le TDA FILE utilise le TDA ELEMENT */

typedef struct {
 	ELEMENT *elements ;
	int debut ;
    int fin ;
 	int longMax ;
 } file,	*FFILE ;


 FFILE FileCreer (int profondeur) ;
 	/* crée et retourne une file vide en lui allouant dynamqiuement de la mémoire */
 void FileDetruire(FFILE);
 	/* libère la mémoire allouée pour la file */

 int FileVide(FFILE);
 	/* teste si la file est vide */

 ELEMENT FileDebut(FFILE);
 	/* retourne l'élément au début de la file sans le retirer de la file */

 ELEMENT FileSortir(FFILE);
 	/* retourne l'élément au début de la file en le retirant de la file */
 int FileEntrer(ELEMENT, FFILE);
 	/* place l'élément à la fin de la file */

 void FileAfficher (FFILE ) ; /* pour test et mise au point */
 void FileRadiographier(FFILE P) ;

 /* void FileRaz(FFILE) ;
    void FileNettoyer(FFILE) ;  ça peut être utile à faire en exercice */

#endif
