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
  if(taille <= 9){
    *tampon = *tampon << 9;
    *tampon = *tampon | (uint32_t) ind;
  }
  else{
    *tampon = *tampon << taille;
    *tampon = *tampon | (uint32_t) ind;
}
}

// Renvoie les 8 octets de poids forts remplis de tampon à écrire
uint8_t Retrait(uint32_t *tampon, int taille_act){
  uint8_t valeur;
// printf("\n\n affichage de tampon initial: %x    \n",*tampon);
  valeur = *tampon >> (taille_act - 8);
  // printf("\n\n affichage de valeur : %x    \n",valeur);
  *tampon = *tampon & ~(valeur << (taille_act - 8));
  // printf("\n\n affichage de tampon : %x    \n",*tampon);
  return valeur;
}


// Complétion puis affichage
uint8_t Completion(uint32_t *tampon, int taille_act){
  uint8_t valeur;
  printf("\n ---- Padding : %d \n", 8 - taille_act);
  valeur = *tampon << (32 - taille_act);
  return valeur;
}
