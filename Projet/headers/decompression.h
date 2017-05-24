#ifndef _DECOMPRESSION_H
#define _DECOMPRESSION_H

#include "dict.h"
void decodage (char* fichier,char* sortie);
int* concat(int* a, int longa, int* b, int longb);
void ecriture(File* s,int* c,int longc);
#endif
