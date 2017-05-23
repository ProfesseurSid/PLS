#include "dict.h"
#include<stdio.h>
#include<stdlib.h>

void decodage (char fichier,Code* D){
  int i,j;
  int* w,x;
  int* a;
  File *f;
  f = fopen(fichier, "r");
  fscanf(f,"%c",&i);
  a = malloc(sizeof(D[i].longeur));
  a = D[i].code;
  if (f != NULL){
    while (!feof(fichier)){
      j = fscanf(f,"%c",&j);
      if (Chercher(D,c,0)){
        x = D[j].code;
      }else{
        x = D[i].code;
        x =
      }
    }
  }else{
    printf("Impossible de lire le fichier\n");
  }
}
