#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include "decompression.h"


int* concat(int* a, int longa, int* b, int longb) {
  int* c = malloc((longa+longb)*sizeof(int));

  for (int i = 0; i < longa; i++) {
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

void ecriture(FILE* s,int* c,int longc) {
  for (int i = 0; i<longc; i++) {
    fputc(c[i],s);
  }
}

void decodage (char* fichier,char* sortie) {
  uint32_t tampon = 0;
  // int lecture;
  int nb_bits_restant = 32;
  int i,j;
  Code ac;
  Code wc;
  Dico D;
  Initialiser(&D);
  int* w, *x = NULL, *a;
  FILE *e = NULL;
  FILE *s = NULL;
  e = fopen(fichier, "r");

  if (e != NULL) {

    fscanf(e,"%d",&i);

    s = fopen(sortie,"w");
    a = malloc(longueur(D,i)*sizeof(int));

    for(j=0; j<longueur(D,i); j++)
      a[j] = element(D,i,j);

    w = malloc(longueur(D,i)*sizeof(int));

    for(j=0; j<longueur(D,i); j++){
      w[j] = a[j];
    }

    ecriture(s,w,longueur(D,i));

    while (!feof(e)) {
      fscanf(e,"%d",&j);
      if(nb_bits_requis(D)>8){
        Ajout(j, &tampon,&nb_bits_restant, D);
        fscanf(e,"%d",&j);
        Ajout(j, &tampon,&nb_bits_restant, D);
        j = Retrait_decompression(&tampon, &nb_bits_restant,D);
      }
      while(nb_bits_restant < (32 - nb_bits_requis(D))){
      if (Appartient(D,j)>0) {
        x = realloc(x, longueur(D,j)*sizeof(int));

        for(int k=0; k<longueur(D,j); k++)
          x[k] = element(D,j,k);

        ecriture(s,x,longueur(D,j));
        a[0] = x[0];
        ac = SequenceVersCode(a,1);
        wc = SequenceVersCode(w,longueur(D,i));
        Inserer(&D,wc,ac);
        i = j;
        w = realloc(w, longueur(D,i)*sizeof(int));

        for(int k=0; k<longueur(D,i); k++)
          w[k] = element(D,i,k);
      } else {
        x = realloc(x, (longueur(D,i)+1)*sizeof(int));

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
  }
    fclose(e);
    fclose(s);
  }else{
    printf("Impossible de lire le fichier\n");
  }
}
