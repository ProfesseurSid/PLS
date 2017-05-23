#ifndef _DICT_H
#define _DICT_H

typedef struct{
	int *code;		// la chaine en question
	int longueur;	// la longueur de la chaine
} Code;

typedef struct{
	Code *dict;
	int nbseq;
}Dico;

void Initialiser(Dico dico);
void Decalage(Dico *dictio, int ind);
Code Fusion(Code prefixe, Code mono);
int Chercher(Dico dico, Code prefixe, Code mono);
Code Inserer(Dico dictio, Code prefixe, Code mono);
int *CodeVersChaine(Code code);
void CopyVersCode(Code new_code, int *seq);
Code SequenceVersCode(int *sequence, int longueur);
int Appartient(Dico dictio, int ind);

#endif
