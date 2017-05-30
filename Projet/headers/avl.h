#ifndef _AVL_H
#define _AVL_H


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max(a,b) ((a)>(b)?(a):(b))

/* structure Dico presentee en cours */

typedef struct n {
  int cle; // L'indice dans le dictionnaire
  struct n *fgauche, *fdroite;
  int *code;
  int longueur;
  int bal; // desequilibre
} Code ;

/* type Dico, pointeur vers un Dico */

typedef Code *Dico; 

int feuille (Dico a);
Dico ajouter_noeud (Dico a, Dico n);
Dico rechercher_cle_arbre (Dico a, int valeur);
int cle_max(Dico a);
void afficher_arbre (Dico a, int niveau);
int hauteur_arbre (Dico a);
void parcourir_arbre (Dico a, int *t, int niveau);
void nombre_noeuds_par_niveau (Dico a);
int nombre_cles_arbre (Dico a);
Dico cle_superieure_arbre (Dico a, int valeur, Dico *sup);
Dico rechercher_cle_sup_arbre (Dico a, int valeur);
Dico rotationDroite(Dico a);
Dico rotationGauche(Dico a);
Dico doubleRotationGauche(Dico a);
Dico doubleRotationDroite(Dico a);
Dico Equilibrage(Dico a);
Dico ajouter_Code (Dico a, int cle, int *sequence, int longueur);
Dico cle_inferieure_arbre (Dico a, int valeur, Dico *inf);
Dico rechercher_cle_inf_arbre (Dico a, int valeur);
int EquilibreComplet1 (Dico a);
int EquilibreComplet2 (Dico a);
// Dico lire_arbre (char *nom_fichier);
Dico detruire_cle_arbre (Dico a, int cle);
int trouver_cle_min (Dico a);
//Dit si l'ensemble des clefs de a1 sont inclues dans a2
int inclusion_arbre (Dico a1, Dico a2);

#endif
