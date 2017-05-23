#ifndef _DICT_H
#define _DICT_H

typedef struct{
	int *code;		// la chaine en question
	int longueur;	// la longueur de la chaine
} Code;

void Initialiser(Code *dict);
Code Inserer(Code *dict, Code prefixe, Code mono);
uint8_t *CodeVersChaine(Code code, int *longueur);
Code SequenceVersCode(uint8_t *sequence, int longueur);

#endif