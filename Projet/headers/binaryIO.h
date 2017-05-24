#ifndef BINARY_IO
#define BINARY_IO


// Calcul le nombre de bit nécessaire pour coder ind
int Taille(int ind);

// Met à jour le tampon avec un nouvel indice et renvoie le nombre de bit supplémentaire utilisé
void Ajout(int ind, uint32_t *tampon, int taille);

// Renvoie les 8 octets de poids forts remplis de tampon à écrire
uint8_t Retrait(uint32_t *tampon, int taille_act);

#endif
