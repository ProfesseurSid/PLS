#include "dict.h"
#include <stdio.h>
#include <stdlib.h>





int* concat(int* a, int longa, int* b, int longb){
  int* c = malloc((longa+longb)*sizeof(int));
  // printf("\n\nTRACE\n");
  for (int i = 0; i < longa; i++){
    printf("%d - ", a[i]);
    c[i] = a[i];
  }
  for (int i = 0; i < longb; i++) {
      printf("%d - ", b[i]);
    c[i+longa] = b[i];
  }
  printf("\n\n");
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
  int* w, *x, *a;
  FILE *e = NULL;
  FILE *s = NULL;
  e = fopen(fichier, "r");
  if (e != NULL){
    fscanf(e,"%d",&i);

    s = fopen(sortie,"w");
    a = malloc(longueur(D,i)*sizeof(int));
    for(j=0; j<longueur(D,i); j++)
      a[j] = element(D,i,j);
    w = malloc(longueur(D,i)*sizeof(int));
    for(j=0; j<longueur(D,i); j++)
      w[j] = a[j];
    ecriture(s,w,longueur(D,i));

    while (!feof(e)){
      fscanf(e,"%d",&j);
      if (element(D,j,0)==element(D,256,0)){
          Initialiser(&D);
          fscanf(e,"%d",&j);
      }
      // printf("cherche %d, appart : %i\n", j, Appartient(D,j)>0);
      if (Appartient(D,j)>0){
        x = malloc(longueur(D,j)*sizeof(int));
        for(int k=0; k<longueur(D,j); k++)
          x[k] = element(D,j,k);
        ecriture(s,x,longueur(D,j));
        a[0] = x[0];
        ac = SequenceVersCode(a,1);
        wc = SequenceVersCode(w,longueur(D,i));
        Inserer(&D,wc,ac);
        i = j;
        w = malloc(longueur(D,i)*sizeof(int));
        for(int k=0; k<longueur(D,i); k++)
          w[k] = element(D,i,k);
      }else{
        x = malloc((longueur(D,i)+1)*sizeof(int));
        for(int k=0; k<longueur(D,i); k++)
          x[k] = element(D,i,k);
        x = concat(x, longueur(D,i), a, 1);

        ecriture(s,x,longueur(D,i)+1);
        a[0] = x[0];
        ac = SequenceVersCode(a,1);
        wc = SequenceVersCode(w,longueur(D,i));
        Inserer(&D,wc,ac);
        i = j;
        for(int k=0; k<longueur(D,i); k++)
          w[k] = element(D,i,k);
      }
    }
    fclose(e);
    fclose(s);
  }else{
    printf("Impossible de lire le fichier\n");
  }
}
