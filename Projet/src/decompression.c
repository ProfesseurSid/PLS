#include "dict.h"
#include<stdio.h>
#include<stdlib.h>

void decodage (char* fichier,char* sortie){
  int i,j;
  Dico D;
  Initialiser(D);
  int* w,x,a;
  File *e = NULL;
  File *s = NULL;
  e = fopen(fichier, "r");
  if (e != NULL){
    fscanf(e,"%c",&i);
    s = fopen(sortie,"w");
    a = malloc(D[i].longueur*sizeof(int));
    for(j=0; j<D[i].longueur; j++)
      a[j] = D[i].code[j];
    w = malloc(sizeof(a));
    for(j=0; j<D[i].longueur; j++)
      w[j] = a[j];
    //fputs(w,s); FONCTION DECRITURE CARAC PAR CARAC
    ecriture(s,w,sizeof(w));
    while (!feof(e)){
      j = fscanf(e,"%c",&j);
      if (j==256){
          Initialiser(D);
          j = fscanf(e,"%c",&j);
      }
      if (Appartient(D,j)>0){
        x = malloc(D[j].longueur*sizeof(int));
        for(int k=0; k<D[j].longueur; k++)
          x[k] = D[j].code[k];
      }else{
        // x = malloc((D[i].longueur+1)*sizeof(int));
        // for(int k=0; k<D[i].longueur; k++)
        //   x[k] = D[i].code[k];
        x = concat(D[i].code, D[i].longueur, a, 1);
      }
      // fputs(x,s); FONCTION DECRITURE CARAC PAR CARAC
      ecriture(s,x,D[i].longueur+1);
      a[0] = x[0];
      Inserer(D,w,a);
      i = j;
      for(int k=0; i<D[i].longueur; k++)
        w[k] = D[i].code[k];
    }
  }else{
    printf("Impossible de lire le fichier\n");
  }
}

int* concat(int* a, int longa, int* b, int longb){
  int* c = malloc((longa+longb)*sizeof(int));
  for (int i = 0; i < longa; i++){
    c[i] = a[i];
  }
  for (int i = longa; i < longa+longb; i++) {
    c[i] = b[i];
  }
  return c;
}

void ecriture(File* s,int* c,int longc){
  for (int i = 0; i<longc; i++){
    fputc(c[i],s);
  }
}
