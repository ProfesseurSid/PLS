// #include "dict.h"
#include <stdio.h>
#include <stdlib.h>

#define NBMAXSEQ 512

void Initialiser(Code *dict){
	for(int i=0; i<255; i++){
		dict[i].code[0] = i;
		dict[i].longueur = 1;
	}
	for(int i=255; i<NBMAXSEQ; i++)
		dict[i].longueur = 0;
}

/* cherche la chaine prefixe+mono dans le tableau. */
/* renvoie faux si la chaine prefixe+mono est présente, -1 si le préfixe est absent aussi, l'indice du préfixe sinon */
int Chercher(Code *dict, Code prefixe, Code mono){
	int i=0;
	int retour = -1;
	while(dict[i].longueur < prefixe.longueur && i<NBMAXSEQ+1){
		i++;
	}
	while(retour < 0 && dict[i].longueur < prefixe.longueur+1){
		for(int j=0; j<dict[i].longueur; )
	}


}

Code Inserer(Code *dict, Code prefixe, Code mono){
	if(chercher(prefixe, mono)){
		/* Insertion d'une fausse ligne tavu */
	}
}