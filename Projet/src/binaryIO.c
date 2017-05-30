#include <stdio.h>
#include <stdlib.h>
#include "binaryIO.h"

// Calcul le nombre de bit nécessaire pour coder une sequence
int nb_bits_requis(Dico dico){
  static int puiss = 0;
  static int nb = 1;
  while(nb < cle_max(dico)){
    puiss++;
    nb *= 2;
  }
  return puiss;
}

// Met à jour le tampon avec un nouvel indice et renvoie le nombre de bit supplémentaire utilisé
// Les bits sont stocké des bits de poids forts vers les bits de poids faibles
// Lorsqu'on a ajouté notre nouveau code, on redécale afin de placer le bit de poids fort sur le bit 31,
// Laissant les bits de poids faibles libre.
void Ajout(int ind, uint32_t *tampon, int *nb_bits_restant, Dico dico){

  int bits = nb_bits_requis(dico);
  *tampon = *tampon >> (*nb_bits_restant - bits);
  *tampon = *tampon | (uint32_t) ind;
  *nb_bits_restant -= bits;
  *tampon = *tampon << (*nb_bits_restant);
}


// Renvoie les 8 octets de poids forts remplis de tampon à écrire
// On décale les bits afin d'avoir les 8 bits que l'on veut sortir en bit de poids faible.
// Puis on fait un masquage afin de remettre ces bits à 0.
// Finalement, on replace la suite de bit en poids fort.
uint8_t Retrait(uint32_t *tampon, int *nb_bits_restant, Dico dico){
  uint8_t valeur;
  valeur = *tampon >> 24;
  *tampon = *tampon & (0x00FFFFFF);
  *tampon = *tampon << 8;

  *nb_bits_restant += 8;
  return valeur;
}



int Retrait_decompression(uint32_t *tampon, int *nb_bits_restant, Dico dico){
  uint8_t valeur;
  valeur = *tampon >> (32-nb_bits_requis(dico));
  *tampon = *tampon << nb_bits_requis(dico);
  nb_bits_restant += nb_bits_requis(dico);
  return valeur;
}