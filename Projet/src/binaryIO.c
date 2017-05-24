#include <stdio.h>
#include <stdlib.h>
#include "binaryIO.h"

// Calcul le nombre de bit nécessaire pour coder ind
int Taille(int ind){
  int taille = 1;
  int total = 1;
  while(total*2<ind){
    taille ++;
    total *= 2;
  }
  return taille;
}

// Met à jour le tampon avec un nouvel indice et renvoie le nombre de bit supplémentaire utilisé
void Ajout(int ind, uint32_t *tampon, int taille){
  *tampon = *tampon << taille;
  *tampon = *tampon | (uint32_t) ind;
}

// Renvoie les 8 octets de poids forts remplis de tampon à écrire
uint8_t Retrait(uint32_t *tampon, int taille_act){
  uint8_t valeur;
  valeur = *tampon >> (taille_act - 8);
  *tampon = *tampon & ~(valeur << (taille_act - 8));
  return valeur;
}
