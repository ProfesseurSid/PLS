#ifndef _DICT_H
#define _DICT_H

typedef struct{
	int *code;		// la chaine en question
	int longueur;	// la longueur de la chaine
} Code;

void Initialiser(Dico dict);
int Chercher(Dico dico, Code prefixe, Code mono);
Code Inserer(Dico dict, Code prefixe, Code mono);
int *CodeVersChaine(Code code);
Code SequenceVersCode(uint8_t *sequence, int longueur);

#endif