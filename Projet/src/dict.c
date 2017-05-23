#include "dict.h"
#include <stdio.h>
#include <stdlib.h>

#define NBMAXSEQ 512

void Initialiser(Dico dico){
	for(int i=0; i<=255; i++){
		dico.dict[i].code[0] = i;
		dico.dict[i].longueur = 1;
	}
	for(int i=256; i<NBMAXSEQ; i++)
		dico.dict[i].longueur = 0;
}

/* cherche la chaine prefixe+mono dans le tableau. */
/* renvoie -1 si la chaine prefixe+mono est présente, -42 si le préfixe est absent aussi, l'indice du préfixe sinon */
int Chercher(Dico dico, Code prefixe, Code mono){
	int i=0, j;
	int retour = -42;
	while((i < NBMAXSEQ) && (dico.dict[i].longueur < prefixe.longueur)){
		i++;
	}
	while((i < NBMAXSEQ) && (retour < 0) && (dico.dict[i].longueur < prefixe.longueur+1)){
		for(j=0; (j < dico.dict[i].longueur) && (dico.dict[i].code[j] == prefixe[j]); j++){}
		if(j == dico.dict[i].longueur)
			retour = i;
	}

	while((i < NBMAXSEQ) && (dico.dict[i].longueur < prefixe.longueur+1)){
		i++;
	}
	while((i < NBMAXSEQ) && (retour >= 0) && (dico.dict[i].longueur < prefixe.longueur+2)){
		for(j=0; (j < dico.dict[i].longueur) && (dico.dict[i].code[j] == prefixe[j]); j++){}
		if((j == dico.dict[i].longueur) && (dico.dict[i].code[j] == mono.code[0]))
			retour = -1;
	}

	return retour;
}

// Fonction de décalage à droite à partir de l'indice
void Decalage(Dico *dictio, int ind){
	int i;
	for(i=dictio.nbseq - 1; i>= ind; i--) {
									dictio.dict[i+1] = dictio.dict[i];
	}
	dictio.nbseq++;
}

// Fusion des deux codes pour former un code : prefixe-mono.
Code Fusion(Code prefixe, Code mono){
	int i;
	Code fusion = malloc(sizeof(Code));
	for(i=0; i<prefixe.longueur; i++) {
									fusion.code[i] = prefixe.code[i];
	}
	fusion.code[i] = mono.code[i];
	fusion.longueur = prefixe.longueur + 1;
	return fusion;
}


//Si <0, on ne peux pas rajouter car soit : préfixe pas présent, ou alors code déjà présent
//Sinon, on effectue le déplacement + le placement du code au bon endroit

// VALEUR DE RETOUR :
// -1 : préfixe ou code déjà présent
// 0 : Dico remplis de ses NBMAXSEQ valeurs
// 1 : le code a été rajouté dans le dico

Code Inserer(Dico *dictio, Code prefixe, Code mono){
	int ind;
	Code fusion;
	fusion = malloc(sizeof(Code));
	ind = chercher(dictio,prefixe,mono);
	if(ind < 0) {
		return -1;
	}
	else if(ind >= 0) {
		Decalage(dictio, ind);
		fusion = Fusion(prefixe,mono);
		dictio.dict[ind] = fusion;
		return 1;
		if(dictio.nbseq < NBMAXSEQ) {
			return 1;
		}
		else{
			return 0;
		}
	}
}

int *CodeVersChaine(Code code){
	int *retour;
	retour = malloc(code.longueur*sizeof(int));
	for(int i=0; i<longueur; i++)
		retour[i] = code.code[i];
	return retour;
}

void CopyVersCode(Code new_code, int *seq){
int i;
for(i = 0; i < new_code.longueur; i++){
	new_code.code[i] = seq[i];
}
}

Code SequenceVersCode(int *sequence, int longueur){
Code new_code = malloc(sizeof(Code));
new_code.longueur = longueur;
CopyversCode(new_code, sequence);
return new_code;
}
