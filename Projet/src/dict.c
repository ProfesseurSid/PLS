#include "dict.h"
#include <stdio.h>
#include <stdlib.h>

#define NBMAXSEQ 512


void Initialiser(Dico *dico){
	dico->dict = malloc(NBMAXSEQ*sizeof(int));
	for(int i=0; i<=256; i++){
		dico->dict[i].code = malloc(sizeof(int));
		dico->dict[i].code[0] = i;
		dico->dict[i].longueur = 1;
	}
	for(int i=0; i<256; i++){
		dico->dict[i].code = malloc(sizeof(int));
		dico->dict[i].code[0] = i;
	}
	for(int i=257; i<NBMAXSEQ; i++)
		dico->dict[i].longueur = 0;
	dico->nbseq = 257;
}

/* cherche la chaine prefixe+mono dans le tableau. */
/* renvoie -1 si la chaine prefixe+mono est présente, -42 si le préfixe est absent aussi, l'indice du préfixe sinon */
int Chercher(Dico dico, Code prefixe, Code mono){
	int i=0;
	int retour = -42;
	// while((i < NBMAXSEQ) && (dico.dict[i].longueur < prefixe.longueur) && (dico.dict[i].longueur > 0)){
	// 	i++;
	// }
	// while((i < NBMAXSEQ) && (retour < 0) && (dico.dict[i].longueur < prefixe.longueur+1) && (dico.dict[i].longueur > 0)){
	// 	for(j=0; (j < dico.dict[i].longueur) && (dico.dict[i].code[j] == prefixe.code[j]); j++){}
	// 	if(j == dico.dict[i].longueur)
	// 		retour = i;
	// 	i++;
	// }

	// while((i < NBMAXSEQ) && (dico.dict[i].longueur < prefixe.longueur+1) && (dico.dict[i].longueur > 0)){
	// 	i++;
	// }
	// while((i < NBMAXSEQ) && (retour >= 0) && (dico.dict[i].longueur < prefixe.longueur+2) && (dico.dict[i].longueur > 0)){
	// 	for(j=0; (j < dico.dict[i].longueur) && (dico.dict[i].code[j] == prefixe.code[j]); j++){}
	// 	if((j == dico.dict[i].longueur) && (dico.dict[i].code[j] == mono.code[0]))
	// 		retour = -1;
	// 	i++;
	// }

	while((i < dico.nbseq) && (retour < 0)){
		// printf("etat : %i dic[%i] = %i\n", i, i, dico.dict[i].code[0]);
		// for(j=0; (prefixe.longueur == dico.dict[i].longueur) && (j < dico.dict[i].longueur) && (dico.dict[i].code[j] == prefixe.code[j]); j++){}
		// if(j == dico.dict[i].longueur)
		// 	retour = i;
		if(dico.dict[i].longueur == prefixe.longueur){
			int idem=1;
			for(int j = 0; j<prefixe.longueur; j++){
				// printf("dico : %c ; pref : %c\n", dico.dict[i].code[j], prefixe.code[j]);
				idem = idem && (dico.dict[i].code[j] == prefixe.code[j]);
			}
			if(idem)
				retour = i;
		}
		i++;
	}
	while((i < dico.nbseq) && (retour >= 0)){
		// for(j=0; (prefixe.longueur == dico.dict[i].longueur-1) && (j < dico.dict[i].longueur) && (dico.dict[i].code[j] == prefixe.code[j]); j++){}
		// j = 0;
		// while((prefixe.longueur == dico.dict[i].longueur-1) && (j < dico.dict[i].longueur) && (dico.dict[i].code[j] == prefixe.code[j])){
		// 	printf("prefixe : %c ; dic : %c ; diclen : %i\n", prefixe.code[j], dico.dict[i].code[j], dico.dict[i].longueur);
		// 	j++;
		// }
		// if((j == dico.dict[i].longueur-1)){
		// 	printf("prefixe+mono : ");
		// 	for(int l = 0; l<prefixe.longueur; l++)
		// 		printf("%c", prefixe.code[l]);
		// 	printf("%c\n", mono.code[0]);
		// 	printf("dico : ");
		// 	for(int l = 0; l<dico.dict[i].longueur; l++)
		// 		printf("%c", dico.dict[i].code[l]);
		// 	printf(" ; diclen : %i\n", dico.dict[i].longueur);
		// }
		// if((j == dico.dict[i].longueur) && (dico.dict[i].code[j] == mono.code[0]))
		// 	retour = -1;
		if(dico.dict[i].longueur == prefixe.longueur+1){
			int idem=1;
			for(int j = 0; j < prefixe.longueur; j++){
				idem = idem && (prefixe.code[j] == dico.dict[i].code[j]);
			}
			idem = idem && (dico.dict[i].code[prefixe.longueur] == mono.code[0]);

			if(idem)
				retour = -1;
		}
		i++;
	}
	printf("retour : %i\n", retour);
	return retour;
}

// Fonction de décalage à droite à partir de l'indice
void Decalage(Dico *dictio, int ind){
	int i;
	for(i=dictio->nbseq - 1; i >= ind; i--) {
		dictio->dict[i+1] = dictio->dict[i];
	}
}

// Fusion des deux codes pour former un code : prefixe-mono.
void Fusion(Code prefixe, Code mono, Code *retour){
	int i;
	// Code fusion;
	retour->code = malloc((prefixe.longueur+1)*sizeof(int));
	for(i=0; i<prefixe.longueur; i++) {
		retour->code[i] = prefixe.code[i];
	}
	retour->code[prefixe.longueur] = mono.code[0];
	retour->longueur = prefixe.longueur + 1;

}


//Si <0, on ne peux pas rajouter car soit : préfixe pas présent, ou alors code déjà présent
//Sinon, on effectue le déplacement + le placement du code au bon endroit

// VALEUR DE RETOUR :
// -1 : préfixe ou code déjà présent
// 0 : Dico remplis de ses NBMAXSEQ valeurs
// 1 : le code a été rajouté dans le dico

int Inserer(Dico *dictio, Code prefixe, Code mono){
	// int ind;
	Code fusion;
	// ind = 0;
	if(Chercher(*dictio,prefixe,mono) < 0) {
		return -1;
	}
	else {
		// Decalage(dictio, ind);
		Fusion(prefixe,mono,&fusion);
		dictio->dict[dictio->nbseq] = fusion;
		dictio->nbseq++;
		if(dictio->nbseq < NBMAXSEQ) {
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
	for(int i=0; i<code.longueur; i++)
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
	Code new_code;
	new_code.code = malloc(longueur*sizeof(int));
	new_code.longueur = longueur;
	CopyVersCode(new_code, sequence);
	return new_code;
}


int Appartient(Dico dictio, int ind){
	if(ind<512){
		return dictio.dict[ind].longueur;
	}
	else return -1;
}
