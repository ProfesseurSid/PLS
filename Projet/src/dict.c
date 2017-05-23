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
/* renvoie -1 si la chaine prefixe+mono est présente, -42 si le préfixe est absent aussi, l'indice du préfixe sinon */
int Chercher(Code *dict, Code prefixe, Code mono){
	int i=0, j;
	int retour = -42;
	while((i < NBMAXSEQ) && (dict[i].longueur < prefixe.longueur)){
		i++;
	}
	while((i < NBMAXSEQ) && (retour < 0) && (dict[i].longueur < prefixe.longueur+1)){
		for(j=0; (j < dict[i].longueur) && (dict[i].code[j] == prefixe[j]); j++){}
		if(j == dict[i].longueur)
			retour = i;
	}

	while((i < NBMAXSEQ) && (dict[i].longueur < prefixe.longueur+1)){
		i++;
	}
	while((i < NBMAXSEQ) && (retour >= 0) && (dict[i].longueur < prefixe.longueur+2)){
		for(j=0; (j < dict[i].longueur) && (dict[i].code[j] == prefixe[j]); j++){}
		if((j == dict[i].longueur) && (dict[i].code[j] == mono.code[0]))
			retour = -1;
	}

	return retour;
}

Code Inserer(Code *dict, Code prefixe, Code mono){
	if(chercher(prefixe, mono) < 0){
		/* Insertion d'une fausse ligne tavu */
	}
}
