#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "avl.h"

#define max(a,b) ((a)>(b)?(a):(b))

int feuille (Dico a)
{
  if (a == NULL)
    return 0 ;
  else
    {
      if ((a->fgauche == NULL) && (a->fdroite == NULL))
	return 1 ;
      else
	return 0 ;
    }
}

Dico ajouter_noeud (Dico a, Dico n)
{
  /* ajouter le noeud n dans l'arbre a */
  if (a == NULL)
    return n ;
  else if (n->cle < a->cle){
    a->fgauche = ajouter_noeud (a->fgauche, n) ;
  }
  else{
    a->fdroite = ajouter_noeud (a->fdroite, n) ;
  }
  return a ;

}

Dico rechercher_cle_arbre (Dico a, int valeur)
{
  if (a == NULL)
    return NULL ;
  else{
    if (a->cle == valeur)
      return a ;
    else{
    	if (a->cle < valeur)
    	 return rechercher_cle_arbre (a->fdroite, valeur) ;
    	else
    	 return rechercher_cle_arbre (a->fgauche, valeur) ;
    }
  }
}

int cle_max (Dico a){
  int l=0,r=0;
  if(a->fdroite != NULL)
    r = cle_max(a->fdroite);
  if(a->fgauche != NULL)
    l = cle_max(a->fgauche);
  return max(a->cle,max(l,r));
}

void afficher_arbre (Dico a, int niveau)
{
  /*
    affichage de l'arbre a
    on l'affiche en le penchant sur sa gauche
    la partie droite (haute) se retrouve en l'air
  */

  int i ;

  if (a != NULL)
    {
      afficher_arbre (a->fdroite,niveau+1) ;

      for (i = 0; i < niveau; i++) printf ("\t") ;
      printf (" %d (%d)(/%d)\n\n", a->cle, niveau, a->bal) ;

      afficher_arbre (a->fgauche, niveau+1) ;
    }
  return ;
}

int hauteur_arbre (Dico a)
{
  /*
    calculer la hauteur de l'arbre a
  */

  if (a == NULL)
    return 0 ;
  else
    {
      return 1 +
       max (hauteur_arbre (a->fgauche), hauteur_arbre (a->fdroite)) ;
    }
}

void parcourir_arbre (Dico a, int *t, int niveau)
{
  if (a == NULL)
    return ;

  t [niveau] = t [niveau] + 1 ;
  parcourir_arbre (a->fgauche, t, niveau+1) ;
  parcourir_arbre (a->fdroite, t, niveau+1) ;

  return ;
}

void nombre_noeuds_par_niveau (Dico a)
{
  int i  ;
  int *t ;
  int h  ;

  h = hauteur_arbre (a) ;

  /* Allocation d'un tableau d'entier, une case par niveau */
  t = malloc (h * sizeof (int)) ;

  /* initialisation du tableau */

  for (i = 0; i < h ; i++)
    t[i] = 0 ;

  /*
     Parcourir l'arbre a partir du niveau 0
     le tableau t est passe en parametre
  */

  parcourir_arbre (a, t, 0) ;

  for (i = 0; i < h ; i++)
    printf ("Niveau %d: nombre cles %d\n", i, t[i]) ;

  free (t) ;
  return ;
}

int nombre_cles_arbre (Dico a)
{
  if (a == NULL)
    return 0 ;
  else
    {
      if(a->longueur > 0)
        return 1 + nombre_cles_arbre (a->fgauche) + nombre_cles_arbre (a->fdroite) ;
      else
        return nombre_cles_arbre (a->fgauche) + nombre_cles_arbre (a->fdroite) ;
    }
}



Dico cle_superieure_arbre (Dico a, int valeur, Dico *sup)
{
  if (a == NULL)
    return *sup ;

  if (valeur < a->cle)
    {
      *sup = a ;
      return cle_superieure_arbre (a->fgauche, valeur, sup) ;
    }
  else if (valeur > a->cle)
    {
      *sup = a ;
      return cle_superieure_arbre (a->fdroite, valeur, sup) ;
    }
  else
    {
      return *sup ;
    }
}

Dico rechercher_cle_sup_arbre (Dico a, int valeur)
{
  Dico ptrouve ;
  Dico psup = NULL ;

  ptrouve = cle_superieure_arbre (a, valeur, &psup) ;
  return ptrouve ;

}

Dico rotationDroite(Dico a){
  // Je deviens le fils droit de mon fils gauche
  if (a != NULL){
    Dico NR = a->fgauche ;
    if(NR!=NULL){
      a->fgauche = NR->fdroite ;
      Dico Pred = rechercher_cle_sup_arbre(a, a->cle) ;
      if(Pred != NULL && Pred->fdroite == a)
        Pred->fdroite = NR ;
      if(Pred != NULL && Pred->fgauche == a)
        Pred->fgauche = NR ;
      NR->fdroite = a ;
      NR->fdroite->bal = hauteur_arbre(NR->fdroite->fdroite) - hauteur_arbre(NR->fdroite->fgauche) ;
      NR->bal = hauteur_arbre(NR->fdroite) - hauteur_arbre(NR->fgauche) ;
      if(NR->fgauche != NULL)
        NR->fgauche->bal = hauteur_arbre(NR->fgauche->fdroite) - hauteur_arbre(NR->fgauche->fgauche) ;
      return NR ;
    }
  }
  return a ;
}

Dico rotationGauche(Dico a){
  // Je deviens le fils gauche de mon fils droit
  if (a != NULL){
    Dico NR = a->fdroite ;
    if(NR != NULL){
      a->fdroite = NR->fgauche ;
      Dico Pred = rechercher_cle_sup_arbre(a, a->cle) ;
      if(Pred != NULL && Pred->fgauche == a)
        Pred->fgauche = NR ;
      if(Pred != NULL && Pred->fdroite == a)
        Pred->fdroite = NR ;
      NR->fgauche = a ;
      NR->fgauche->bal = hauteur_arbre(NR->fgauche->fdroite) - hauteur_arbre(NR->fgauche->fgauche) ;
      NR->bal = hauteur_arbre(NR->fdroite) - hauteur_arbre(NR->fgauche) ;
      if (NR->fdroite != NULL)
        NR->fdroite->bal = hauteur_arbre(NR->fdroite->fdroite) - hauteur_arbre(NR->fdroite->fgauche) ;
      return NR ;
    }
  }
  return a ;
}

Dico doubleRotationGauche(Dico a){
  // Je deviens le fils gauche du fils gauche de mon fils droit
  a->fdroite = rotationDroite(a->fdroite) ;
  return rotationGauche(a) ;
}

Dico doubleRotationDroite(Dico a){
  // Je deviens le fils droit du fils droit de mon fils gauche
  a->fgauche = rotationGauche(a->fgauche) ;
  return rotationDroite(a) ;
}

Dico Equilibrage(Dico a){

  if (a->bal >= 2){
    if (a->fdroite->bal >= 0){
      return rotationGauche(a) ;
    }
    else{
      return doubleRotationGauche(a) ;
    }
  }
  else if (a->bal <= -2){
    if (a->fgauche->bal <= 0){
      return rotationDroite(a) ;
    }
    else{
      return doubleRotationDroite(a) ;
    }
  }
  else{
    return a ;
  }
}

Dico ajouter_Code (Dico a, int cle, int *sequence, int longueur)
{
  Dico n ;
  Dico ptrouve ;

  /*
     ajout de la clé. Creation du noeud n qu'on insere
    dans l'arbre a
  */

  ptrouve = rechercher_cle_arbre (a, cle) ;

  if (ptrouve == NULL)
  {
    n = malloc (sizeof(Code)) ;
    n->cle = cle;
    n->longueur = longueur;
    // printf("longueur : %i\n", n->longueur);
    n->code = malloc(longueur*sizeof(int));
    for(int i=0; i<longueur; i++)
      n->code[i] = sequence[i];
    n->fgauche = NULL ;
    n->fdroite = NULL ;
    n->bal = 0 ;
    a = ajouter_noeud (a, n) ;
    Dico AC=rechercher_cle_sup_arbre(a, n->cle) ;
    while(AC!=NULL && AC->bal<2 && AC->bal>-2){
      AC->bal = hauteur_arbre(AC->fdroite) - hauteur_arbre(AC->fgauche) ;
      if (AC->bal<2 && AC->bal>-2)
        AC = rechercher_cle_sup_arbre(a, AC->cle) ;
    }

    if (AC != NULL){
      Dico Pred = rechercher_cle_sup_arbre(a, AC->cle) ;
      if (Pred == NULL){
        a = Equilibrage(a) ;
      }
      else if (Pred->cle < AC->cle){
        Pred->fdroite = Equilibrage(AC) ;
      }
      else{
        Pred->fgauche = Equilibrage(AC) ;
      }
    }

    return a ;
  }
  else
    return a ;
}

Dico cle_inferieure_arbre (Dico a, int valeur, Dico *inf)
{
  if (a == NULL)
    return *inf ;

  if (valeur > a->cle)
    {
      *inf = a ;
      return cle_inferieure_arbre (a->fdroite, valeur, inf) ;
    }
  else
    {
      return cle_inferieure_arbre (a->fgauche, valeur, inf) ;
    }
}

Dico rechercher_cle_inf_arbre (Dico a, int valeur)
{
  Dico ptrouve ;
  Dico pinf = NULL ;

  ptrouve = cle_inferieure_arbre (a, valeur, &pinf) ;
  return ptrouve ;
}

int EquilibreComplet1 (Dico a)
{
  int h ;
  int nbcles;

  int p = 1 ;

  h = hauteur_arbre (a) ;
  p = (p << h) - 1  ;

  nbcles = nombre_cles_arbre (a) ;

  if (p == nbcles)
    return 1 ;
  else
    return 0 ;
}

int EquilibreComplet2 (Dico a)
{

  if (a == NULL)
    return 1 ;

  if ((a->fgauche != NULL && a->fdroite == NULL) || (a->fgauche == NULL && a->fdroite != NULL))
    return 0 ;

  return (EquilibreComplet2 (a->fgauche) && EquilibreComplet2 (a->fdroite)) ;
}


Dico detruire_cle_arbre (Dico a, int cle)
{
  Dico AC = NULL ;
  // Si la cle est absente ou l'arbre vide, renvoie l'arbre tel quel
  if((a == NULL) || (rechercher_cle_arbre(a,cle) == NULL))
    return a ;
  // Si on supprime la racine : le fils droit devient la racine
  // Puis on ajoute l'arborescence du fils droit a ce nouvel arbre
  // Enfin, on equilibre si besoin
  else if(a->cle == cle)
  {
    if(a->fdroite==NULL)
      return a->fgauche ;
    AC = a->fdroite ;
    if(a->fgauche != NULL)
      ajouter_noeud(a->fdroite,a->fgauche) ;

    if(AC->fgauche != NULL)
      AC->fgauche->bal = hauteur_arbre(AC->fgauche->fdroite) - hauteur_arbre(AC->fgauche->fgauche) ;
    if(AC->fgauche != NULL && (AC->fgauche->bal<-1 || AC->fgauche->bal>1))
      AC->fgauche = Equilibrage(AC->fgauche) ;
    if(AC->fdroite != NULL)
      AC->fdroite->bal = hauteur_arbre(AC->fdroite->fdroite) - hauteur_arbre(AC->fdroite->fgauche) ;
    if(AC->fdroite != NULL && (AC->fdroite->bal<-1 || AC->fdroite->bal>1))
      AC->fdroite = Equilibrage(AC->fdroite) ;

    AC->bal = hauteur_arbre(AC->fdroite) - hauteur_arbre(AC->fgauche) ;
    if(AC->bal < -1 || AC->bal > 1)
      AC = Equilibrage(AC) ;
    return AC ;
  }
  // Si on supprime une cle au sein de l'arbre : On cherche la cle
  // Puis on stocke ses fils droit et gauche
  // On supprime la cle recherchee et son arborescence
  // Enfin, on ajoute les arbres stockes au nouvel arbre
  // Et on reequilibre si necessaire
  else
  {
    Dico AP = NULL ;
    Dico AD = NULL ;
    Dico Temp = NULL ;
    AC = rechercher_cle_arbre(a, cle) ;

    if(AC != NULL){ // Ne dois pas pouvoir se produire grace au tout premier test, mais est une securite supplementaire
      if(AC->fgauche != NULL)
        AP=AC->fgauche ;
      if(AC->fdroite != NULL)
        AD=AC->fdroite ;
      Dico Pred = rechercher_cle_sup_arbre(a, cle) ;
      if(cle < Pred->cle)
        Pred->fgauche = NULL ;
      else
        Pred->fdroite = NULL ;
      if(AP != NULL)
        a = ajouter_noeud(a,AP) ;
      if(AD != NULL)
        a = ajouter_noeud(a,AD) ;

      if(AP != NULL){
        Temp = rechercher_cle_sup_arbre(a, AP->cle) ;
        AP = rechercher_cle_arbre(a, AP->cle) ;
        AP->bal = hauteur_arbre(AP->fdroite) - hauteur_arbre(AP->fgauche) ;
        if(AP->bal < -1 || AP->bal > 1)
          AP = Equilibrage(AP) ;
        if(AP->cle < Temp->cle)
          Temp->fgauche = AP ;
        if(AP->cle > Temp->cle)
          Temp->fdroite = AP ;
      }
      if(AD != NULL){
        Temp = rechercher_cle_sup_arbre(a, AD->cle) ;
        AD = rechercher_cle_arbre(a, AD->cle) ;
        AD->bal = hauteur_arbre(AD->fdroite) - hauteur_arbre(AD->fgauche) ;
        if(AD->bal < -1 || AD->bal > 1)
          AD = Equilibrage(AD) ;
        if(AD->cle < Temp->cle)
          Temp->fgauche = AD ;
        if(AD->cle > Temp->cle)
          Temp->fdroite = AD ;
      }

      while(Pred != NULL){
        Temp = NULL;
        Pred->bal = hauteur_arbre(Pred->fdroite) - hauteur_arbre(Pred->fgauche) ;
        if(Pred->bal < -1 || Pred->bal > 1){
          Temp = Equilibrage(Pred) ;
          if(cle == 15) printf("%i\n", Temp->cle);
        }
        Pred = rechercher_cle_sup_arbre(a, Pred->cle) ;
        if (Temp != NULL && Pred != NULL && Temp->cle < Pred->cle)
          Pred->fgauche = Temp ;
        if (Temp != NULL && Pred != NULL && Temp->cle > Pred->cle)
          Pred->fdroite = Temp ;
        if (Temp != NULL && Pred == NULL)
          a = Temp ;
      }
    }
    return a ;
  }
}

int trouver_cle_min (Dico a)
{
  Dico AC = NULL;

  // On cherche la feuille la plus a gauche de l'arbre
  if(a == NULL)
  {
    return 0;
  }
  else
  {
    AC = a;
    while(AC->fgauche != NULL)
    {
      AC = AC->fgauche;
    }
    return AC->cle;
  }
}

//Dit si l'ensemble des clefs de a1 sont inclues dans a2
int inclusion_arbre (Dico a1, Dico a2)
{
  // Renvoie le booleen "la cle actuelle est dans a2, et l'ensemble des cles de mes fils aussi"
  if(a1!=NULL){
    return ((rechercher_cle_arbre(a2, a1->cle)!=NULL) && inclusion_arbre(a1->fgauche, a2) && inclusion_arbre(a1->fdroite, a2));
  }
  else{
    return 1;
  }

}
