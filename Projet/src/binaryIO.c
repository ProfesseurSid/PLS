#include <stdio.h>
#include <stdlib.h>
#include "binaryIO.h"

// Calcul le nombre de bit nécessaire pour coder un indice
int nb_bits_requis(int ind){
  static int puiss = 0;
  static int nb = 1;
  while(nb < ind){
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

  int bits = nb_bits_requis(nombre_elements(dico));
  *nb_bits_restant -= bits;
  *tampon = ((*tampon >> (*nb_bits_restant)) | (uint32_t) ind) << (*nb_bits_restant);
  #ifdef DEBUG
  printf("TAMPON : %0x + ajout : %0x\n", *tampon, (uint32_t)ind);
  #endif
}


// Renvoie les 8 octets de poids forts remplis de tampon à écrire
// On décale les bits afin d'avoir les 8 bits que l'on veut sortir en bit de poids faible.
// Puis on fait un masquage afin de remettre ces bits à 0.
// Finalement, on replace la suite de bit en poids fort.
uint8_t Retrait(uint32_t *tampon, int *nb_bits_restant, Dico dico){
  uint8_t valeur;
  valeur = *tampon >> 24;
  *tampon = (*tampon & (0x00FFFFFF)) << 8;
  *nb_bits_restant += 8;
  return valeur;
}


// Ajout version décompression : on ajoute dans le tampon les bits lu
void Ajout_decompression(int ind, uint32_t *tampon, int *nb_bits_restant, Dico dico){
  *nb_bits_restant -= 8;
  *tampon = ((*tampon >> (*nb_bits_restant)) | (uint32_t) ind) << (*nb_bits_restant);
}


// Retrait version décompression : on effectue un retrait du nombre de bits requis par l'arbre
int Retrait_decompression(uint32_t *tampon, int *nb_bits_restant, Dico dico){
  uint32_t valeur;
  int bits = nb_bits_requis(nombre_elements(dico));
  valeur = *tampon >> (32-bits);
  *tampon = *tampon << bits;
  *nb_bits_restant += bits;
  return (int)valeur;
}
