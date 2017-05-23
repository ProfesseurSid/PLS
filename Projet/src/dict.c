// #include "dict.h"
#include <stdio.h>
#include <stdlib.h>

#define NBMAXSEQ 512

void Initialiser(Code *dict){
								for(int i=0; i<255; i++) {
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
								while((i < NBMAXSEQ) && (dict[i].longueur < prefixe.longueur)) {
																i++;
								}
								while((i < NBMAXSEQ) && (retour < 0) && (dict[i].longueur < prefixe.longueur+1)) {
																for(j=0; (j < dict[i].longueur) && (dict[i].code[j] == prefixe[j]); j++) {}
																if(j == dict[i].longueur)
																								retour = i;
								}
								while((i < NBMAXSEQ) && (dict[i].longueur < prefixe.longueur+1)) {
																i++;
								}
								while((i < NBMAXSEQ) && (retour >= 0) && (dict[i].longueur < prefixe.longueur+2)) {
																for(j=0; (j < dict[i].longueur) && (dict[i].code[j] == prefixe[j]); j++) {}
																if((j == dict[i].longueur) && (dict[i].code[j] == mono.code[0]))
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
								Code fusion;
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
