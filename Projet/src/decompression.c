#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include "decompression.h"
#include "binaryIO.h"


int* concat(int* a, int longa, int* b, int longb) {
  int* c = malloc((longa+longb)*sizeof(int));

  for (int i = 0; i < longa; i++) {
    c[i] = a[i];
  }

  for (int i = 0; i < longb; i++) {
    c[i+longa] = b[i];
  }

  return c;
}

void ecriture(FILE* s,int* c,int longc) {
  for (int i = 0; i<longc; i++) {
    fputc(c[i],s);
  }
}

void decodage (char* fichier,char* sortie) {
  uint32_t tampon = 0;
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

    for(int k=0; k<longueur(D,(int)i); k++)
      w[k] = a[k];

    ecriture(s,w,longueur(D,(int)i));

    while (!feof(e)) {
      if(nb_bits_requis(nombre_elements(D)+1) > (32 - nb_bits_restant)){
        j = fgetc(e);

        Ajout_decompression(j, &tampon, &nb_bits_restant, D);
        }
      if(nb_bits_requis(nombre_elements(D)+1) > (32 - nb_bits_restant)){
        j = fgetc(e);
        Ajout_decompression(j, &tampon,&nb_bits_restant, D);
        j = Retrait_decompression(&tampon, &nb_bits_restant,D);
        #ifdef DEBUG
        printf("J : %i ; bitsreq : %i\n", j, nb_bits_requis(nombre_elements(D)+1));
        #endif
      }
      else{
        j = Retrait_decompression(&tampon, &nb_bits_restant, D);
        #ifdef DEBUG
        printf("J : %i ; bitsreq : %i\n", j, nb_bits_requis(nombre_elements(D)+1));
        #endif

      }
      if (Appartient(D,j)>0) {
        x = malloc(longueur(D,j)*sizeof(int));

        for(int k=0; k<longueur(D,j); k++)
          x[k] = element(D,(int) j,k);

        ecriture(s,x,longueur(D,(int) j));
        a[0] = x[0];
        ac = SequenceVersCode(a,1);
        wc = SequenceVersCode(w,longueur(D,i));
        Inserer(&D,wc,ac);
        i = j;
        w = malloc(longueur(D,i)*sizeof(int));
        #ifdef DEBUG
        printf("I : %i ; J : %i\n", i, j);
        printf("wk%i : ", i);
        #endif
        for(int k=0; k<longueur(D,i); k++){
          w[k] = element(D,i,k);
          #ifdef DEBUG
          printf("%c", w[k]);
          #endif
        }
        #ifdef DEBUG
        printf("\n");
        #endif

      } else {
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

        #ifdef DEBUG
        printf("I : %i ; J : %i\n", i, j);
        printf("wk%i : ", i);
        #endif
        for(int k=0; k<longueur(D,i); k++){
          w[k] = element(D,i,k);
          #ifdef DEBUG
          printf("%c", w[k]);
          #endif
        }
        #ifdef DEBUG
        printf("\n");
        #endif
      }


    }
    fclose(e);
    fclose(s);
  }else{
    printf("Impossible de lire le fichier\n");
  }
}
