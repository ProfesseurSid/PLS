#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include "decompression.h"
#include "binaryIO.h"


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

  printf("\n");
  return c;
}

void ecriture(FILE* s,int* c,int longc) {
  for (int i = 0; i<longc; i++) {
    // printf("%c", c[i]);
    fputc(c[i],s);
  }
}

void decodage (char* fichier,char* sortie) {
  uint32_t tampon = 0;
  // int lecture;
  int nb_bits_restant = 32;
  int i;
  int j;
  Code ac;
  Code wc;
  Dico D;
  Initialiser(&D);
  int* w, *x = NULL, *a;
  FILE *e = NULL;
  FILE *s = NULL;
  e = fopen(fichier, "r");

  if (e != NULL) {

    i = fgetc(e);

    s = fopen(sortie,"w");
    a = malloc(longueur(D,(int) i)*sizeof(int));
    for(int k=0; k<longueur(D,(int)i); k++)
      a[k] = element(D,i,k);

    w = malloc(longueur(D,(int)i)*sizeof(int));

    for(int k=0; k<longueur(D,(int)i); k++){
      w[k] = a[k];
    }
    ecriture(s,w,longueur(D,(int)i));

    while (!feof(e)) {
      if(nb_bits_requis(cle_max(D)+1) > (32 - nb_bits_restant)){
        j = fgetc(e);
      // printf("GET1 : %0x\n", j);
        Ajout_decompression(j, &tampon, &nb_bits_restant, D);
      // printf("NBBITSRESTANT %i\n", nb_bits_restant);
      }
      if(nb_bits_requis(cle_max(D)+1) > (32 - nb_bits_restant)){
        j = fgetc(e);
        // printf("GET2 : %0x\n", j);
        Ajout_decompression(j, &tampon,&nb_bits_restant, D);
        j = Retrait_decompression(&tampon, &nb_bits_restant,D);
        // printf("J : %i ; bitsreq : %i\n", j, nb_bits_requis(cle_max(D)+1));        
      }
      else{
        j = Retrait_decompression(&tampon, &nb_bits_restant, D);
        // printf("J : %i ; bitsreq : %i\n", j, nb_bits_requis(cle_max(D)+1));
      }
      if (Appartient(D,j)>0) {
        x = realloc(x, longueur(D,j)*sizeof(int));

        for(int k=0; k<longueur(D,j); k++)
          x[k] = element(D,(int) j,k);

        ecriture(s,x,longueur(D,(int) j));
        a[0] = x[0];
        ac = SequenceVersCode(a,1);
        wc = SequenceVersCode(w,longueur(D,i));
        Inserer(&D,wc,ac);
        i = j;
        w = realloc(w, longueur(D,i)*sizeof(int));

        printf("I : %i ; J : %i\n", i, j);
        printf("wk%i : ", i);
        for(int k=0; k<longueur(D,i); k++){
          w[k] = element(D,i,k);
          printf("%c", w[k]);
        }
        printf("\n");
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

        printf("I : %i ; J : %i\n", i, j);
        printf("wk%i : ", i);
        for(int k=0; k<longueur(D,i); k++){
          w[k] = element(D,i,k);
          printf("%c", w[k]);
        }
        printf("\n");
      }
      // printf("nbseq : %i ; nbreq : %i\n", cle_max(D), nb_bits_requis(cle_max(D)+1));
      // j = fgetc(e);
      // Ajout_decompression(j, &tampon, &nb_bits_restant, D);
      // printf("NBBITSRESTANT %i\n", nb_bits_requis(cle_max(D)+1));
      // if(nb_bits_requis(cle_max(D)+1) > (32 - nb_bits_restant)){
      //   printf("ICI\n");
      //   j = fgetc(e);
      //   Ajout_decompression(j, &tampon,&nb_bits_restant, D);
      //   j = Retrait_decompression(&tampon, &nb_bits_restant,D);
      //   printf("J : %i\n", j);        
      // }
      // else{
      //   j = Retrait_decompression(&tampon, &nb_bits_restant, D);
      //   printf("J : %i\n", j);      
      // }
    }
    fclose(e);
    fclose(s);
  }else{
    printf("Impossible de lire le fichier\n");
  }
}
