#ifndef _DICT_H
#define _DICT_H

#include "avl.h"

void Initialiser(Dico *dico);
void Decalage(Dico *dictio, int ind);
void Fusion(Code prefixe, Code mono, Code *retour);
int Chercher(Dico dico, Code prefixe, Code mono);
int Inserer(Dico *dictio, Code prefixe, Code mono);
int *CodeVersChaine(Code code);
void CopyVersCode(Code new_code, int *seq);
Code SequenceVersCode(int *sequence, int longueur);
int Appartient(Dico dictio, int ind);
int longueur(Dico dictio, int ind);
int element(Dico dictio, int ind, int elem);

#endif
