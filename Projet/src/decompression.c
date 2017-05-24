#include "dict.h"
#include<stdio.h>
#include<stdlib.h>





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

void ecriture(FILE* s,int* c,int longc){
  for (int i = 0; i<longc; i++){
    fputc(c[i],s);
  }
}
void decodage (char* fichier,char* sortie){
  int i,j;
  Code ac;
  Code wc;
  Dico D;
  Initialiser(&D);
  int* w,*x,*a;
  FILE *e = NULL;
  FILE *s = NULL;
  e = fopen(fichier, "r");
  if (e != NULL){
    fscanf(e,"%d",&i);
    s = fopen(sortie,"w");
    a = malloc(D.dict[i].longueur*sizeof(int));
    for(j=0; j<D.dict[i].longueur; j++)
      a[j] = D.dict[i].code[j];
    w = malloc(sizeof(a));
    for(j=0; j<D.dict[i].longueur; j++)
      w[j] = a[j];
    //fputs(w,s); FONCTION DECRITURE CARAC PAR CARAC
    ecriture(s,w,sizeof(w));
    while (!feof(e)){

      fscanf(e,"%d",&j);
      if (j==256){
          Initialiser(&D);
          fscanf(e,"%d",&j);
      }
      if (Appartient(D,j)>0){
        x = malloc(D.dict[j].longueur*sizeof(int));
        for(int k=0; k<D.dict[j].longueur; k++)
          x[k] = D.dict[j].code[k];
      }else{
        // x = malloc((D.dict[i].longueur+1)*sizeof(int));
        // for(int k=0; k<D.dict[i].longueur; k++)
        //   x[k] = D.dict[i].code[k];
        x = concat(D.dict[i].code, D.dict[i].longueur, a, 1);
      }
      // fputs(x,s); FONCTION DECRITURE CARAC PAR CARAC
      ecriture(s,x,D.dict[i].longueur+1);
      a[0] = x[0];
      ac = SequenceVersCode(a,1);
      wc = SequenceVersCode(w,D.dict[j].longueur);
      Inserer(&D,wc,ac);
      i = j;
      for(int k=0; i<D.dict[i].longueur; k++)
        w[k] = D.dict[i].code[k];
    }
    fclose(e);
    fclose(s);
  }else{
    printf("Impossible de lire le fichier\n");
  }
}
