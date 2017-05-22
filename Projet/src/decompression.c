#include "dict.h"
#include<stdio.h>
#include<stdlib.h>

void decodage (char fichier){
  int i,j;
  File *f;
  f = fopen(fichier, "r");
  if (f != NULL){
    while (fscanf(f,"%c",&i)){
      j = fscanf(f,"%c",&j);
    }
  }else{
    printf("Impossible de lire le fichier\n");
  }
}
