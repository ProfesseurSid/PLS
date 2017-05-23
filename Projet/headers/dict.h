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

void Initialiser(Code *dict);
void Decalage(Dico *dictio, int ind);
Code Fusion(Code prefixe, Code mono);
Code Inserer(Dico *dictio, Code prefixe, Code mono);
uint8_t *CodeVersChaine(Code code, int *longueur);
Code SequenceVersCode(uint8_t *sequence, int longueur);

#endif
