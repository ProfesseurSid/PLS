#ifndef _DICT_H
#define _DICT_H

void Initialiser();
Code Inserer(Code prefixe, Code mono);
uint8_t *CodeVersChaine(Code code, int *longueur);
Code SequenceVersCode(uint8_t *sequence, int longueur);

#endif