#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max(a,b) ((a)>(b)?(a):(b))

/* structure Dico presentee en cours */

typedef struct n {
  int cle; // L'indice dans le dictionnaire
  struct n *fgauche, *fdroite;
  int *code;
  int bal; // desequilibre
} Dico ;

/* type Arbre, pointeur vers un Dico */

typedef Dico *Arbre; 

/* n nouveau n a ajouter dans l'arbre a */

typedef struct
{
  int tete,queue,taille;
  Arbre *tab;
} file;
void init(file *f, int nbelem)
int empty(file *f)
Arbre get(file *f)
void put(file *f, Arbre a)
int feuille (Arbre a)
Arbre ajouter_Dico (Arbre a, Arbre n)
Arbre rechercher_cle_arbre (Arbre a, int valeur)
void afficher_arbre (Arbre a, int niveau)
int hauteur_arbre (Arbre a)
void parcourir_arbre (Arbre a, int *t, int niveau)
void nombre_Dicos_par_niveau (Arbre a)
int nombre_cles_arbre (Arbre a)
Arbre cle_superieure_arbre (Arbre a, int valeur, Arbre *sup)
Arbre rechercher_cle_sup_arbre (Arbre a, int valeur)
Arbre rotationDroite(Arbre a)
Arbre rotationGauche(Arbre a)
Arbre doubleRotationGauche(Arbre a)
Arbre doubleRotationDroite(Arbre a
Arbre Equilibrage(Arbre a)
Arbre ajouter_cle (Arbre a, int cle)
Arbre cle_inferieure_arbre (Arbre a, int valeur, Arbre *inf)
Arbre rechercher_cle_inf_arbre (Arbre a, int valeur)
int EquilibreComplet1 (Arbre a)
int EquilibreComplet2 (Arbre a)
Arbre lire_arbre (char *nom_fichier)
Arbre detruire_cle_arbre (Arbre a, int cle)
int trouver_cle_min (Arbre a)
void imprimer_liste_cle_triee (Arbre a)
void parcourir_arbre_largeur (Arbre a)
Arbre union_deux_arbres (Arbre a1, Arbre a2)
Arbre intersection_deux_arbres (Arbre a1, Arbre a2)
//Dit si l'ensemble des clefs de a1 sont inclues dans a2
int inclusion_arbre (Arbre a1, Arbre a2)


