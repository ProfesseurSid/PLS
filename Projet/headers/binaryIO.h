#ifndef BINARY_IO
#define BINARY_IO

#include <stdint.h>
#include "dict.h"

// Calcul le nombre de bit nécessaire pour coder ind
int Taille(int ind);

// Met à jour le tampon avec un nouvel indice et renvoie le nombre de bit supplémentaire utilisé
void Ajout(int ind, uint32_t *tampon, int *nb_bits_restant, Dico dico);

// Renvoie les 8 octets de poids forts remplis de tampon à écrire
uint8_t Retrait(uint32_t *tampon, int *nb_bits_restant, Dico dico);

// uint8_t Completion(uint32_t *tampon, int taille_act);
int nb_bits_requis(int ind);

void Ajout_decompression(int ind, uint32_t *tampon, int *nb_bits_restant, Dico dico);

int Retrait_decompression(uint32_t *tampon, int *nb_bits_restant, Dico dico);

#endif
