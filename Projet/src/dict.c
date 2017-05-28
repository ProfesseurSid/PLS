#include "dict.h"
#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

#define NBMAXSEQ 512

void Initialiser(Dico *dico){
	*dico = realloc (*dico, sizeof(Code)) ;
    (*dico)->cle = 0;
    (*dico)->longueur = 1;
    (*dico)->code = malloc(sizeof(int));
    (*dico)->code[0] = 0;
    (*dico)->fgauche = NULL ;
    (*dico)->fdroite = NULL ;
    (*dico)->bal = 0 ;
	for(int i=1; i<=255; i++){
		*dico = ajouter_Code(*dico, i, &i, 1);
	}
}

/* cherche la chaine prefixe+mono dans le tableau. */
/* renvoie -1 si la chaine prefixe+mono est présente, -42 si le préfixe est absent aussi, l'indice du préfixe sinon */
int Chercher(Dico dico, Code prefixe, Code mono){
	int i=0;
	int retour = -42;
	
	while((i < nombre_cles_arbre(dico)) && (retour < 0)){
		// printf("etat : %i dic[%i] = %i\n", i, i, dico.dict[i].code[0]);
		if(rechercher_cle_arbre(dico,i)->longueur == prefixe.longueur){
			int idem=1;
			for(int j = 0; j<prefixe.longueur; j++){
				// printf("dico : %c ; pref : %c\n", dico.dict[i].code[j], prefixe.code[j]);
				idem = idem && (rechercher_cle_arbre(dico,i)->code[j] == prefixe.code[j]);
			}
			if(idem)
				retour = i;
		}
		i++;
	}
	while((i < nombre_cles_arbre(dico)) && (retour >= 0)){
		// printf("lg : %i, %i\n", rechercher_cle_arbre(dico,i)->longueur, prefixe.longueur);
		// printf("long du pref : %i\n", prefixe.longueur);
		// printf("lond de lele %i : %i\n", i, rechercher_cle_arbre(dico,i)->longueur);
		if(rechercher_cle_arbre(dico,i)->longueur == prefixe.longueur+1){
			// printf("OUIOUIOUI\n");
			int idem=1;
			for(int j = 0; j < prefixe.longueur; j++){
				idem = idem && (prefixe.code[j] == rechercher_cle_arbre(dico,i)->code[j]);
			}
			// printf("idem : %i\n", idem);
			idem = idem && (rechercher_cle_arbre(dico,i)->code[prefixe.longueur] == mono.code[0]);
			// printf("idem : %i\n", idem);

			if(idem)
				retour = -1;
		}
		i++;
	}
	// printf("retour : %i\n", retour);
	return retour;
}

// Fonction de décalage à droite à partir de l'indice
// void Decalage(Dico *dictio, int ind){
// 	int i;
// 	for(i=dictio->nbseq - 1; i >= ind; i--) {
// 		dictio->dict[i+1] = dictio->dict[i];
// 	}
// }

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
	// printf("len : %i\n", retour->longueur);
}


//Si <0, on ne peux pas rajouter car soit : préfixe pas présent, ou alors code déjà présent
//Sinon, on effectue le déplacement + le placement du code au bon endroit

// VALEUR DE RETOUR :
// -1 : préfixe ou code déjà présent
// 0 : Dico rempli de ses NBMAXSEQ valeurs
// 1 : le code a été rajouté dans le dico


// Changer pour renvoie code peut être. 
int Inserer(Dico *dictio, Code prefixe, Code mono){
	Code fusion;
	if(Chercher(*dictio,prefixe,mono) < 0) {
		return -1;
	}
	else {
		Fusion(prefixe,mono,&fusion);
		printf("nbc : %i\n", nombre_cles_arbre(*dictio));
		*dictio = ajouter_Code(*dictio, cle_max(*dictio)+1, fusion.code, fusion.longueur);
		// printf("leeeeeen : %i\n",fusion.longueur);
		// printf("but len : %i\n", rechercher_cle_arbre(*dictio, cle_max(*dictio))->longueur);
		if(nombre_cles_arbre(*dictio) < NBMAXSEQ) {
			return 1;
		}
		else{
			Initialiser(dictio);
			return 1;
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
	new_code.fgauche = NULL;
	new_code.fdroite = NULL;
	CopyVersCode(new_code, sequence);
	return new_code;
}


int Appartient(Dico dictio, int ind){
	return rechercher_cle_arbre(dictio,ind)!=NULL;
}

int longueur(Dico dictio, int ind){
	if(rechercher_cle_arbre(dictio,ind) != NULL)
		return rechercher_cle_arbre(dictio,ind)->longueur;
	else
		return 0;
}

int element(Dico dictio, int ind, int elem){
	if(rechercher_cle_arbre(dictio,ind) != NULL)
		return rechercher_cle_arbre(dictio,ind)->code[elem];
	else
		return -1;
}