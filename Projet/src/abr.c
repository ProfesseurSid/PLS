#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "abr.h"

#define max(a,b) ((a)>(b)?(a):(b))

/* structure noeud presentee en cours */

// typedef struct n {
//   int cle;
//   struct n *fgauche, *fdroite;
// } noeud ;

// /* type Arbre, pointeur vers un noeud */

// typedef noeud *Arbre; 

// /* n nouveau n a ajouter dans l'arbre a */

// typedef struct
// {
//   int tete,queue,taille;
//   Dico *tab;
// } file;


// void init(file *f, int nbelem)
// {
//   f->tete = 0;
//   f->queue = 0;
//   f->taille = nbelem;
//   f->tab = malloc(nbelem * sizeof(Arbre));
// }

// int empty(file *f)
// {
//   return f->tete == f->queue;
// }

// Dico get(file *f)
// {
//   Dico e;
//   if(empty(f)) return NULL;
//   else
//   {
//     e = f->tab[f->tete];
//     f->tete = (f->tete + 1)%f->taille;
//   }
//   return e;
// }

// void put(file *f, Dico a)
// {
//   f->tab[f->queue] = a;
//   f->queue =(1 + f->queue)%f->taille;
// }

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
  else if (n->cle < a->cle)
	a->fgauche = ajouter_noeud (a->fgauche, n) ;
  else
	a->fdroite = ajouter_noeud (a->fdroite, n) ;
  return a ;
  
}  

Dico rechercher_cle_arbre (Dico a, int valeur)
{
  if (a == NULL)
    return NULL ;
  else
    {
      if (a->cle == valeur)
	return a ;
      else
	{
	  if (a->cle < valeur)
	    return rechercher_cle_arbre (a->fdroite, valeur) ;
	  else
	    return rechercher_cle_arbre (a->fgauche, valeur) ;
	}
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
      n = (Dico ) malloc (sizeof(Code)) ;
      n->cle = cle;
      n->longueur = longueur;
      n->fgauche = NULL ;
      n->fdroite = NULL ;

      n->code = malloc(longueur*sizeof(int));
      for(int i=0; i<longueur; i++)
        n->code[i] = sequence[i];

      a = ajouter_noeud (a, n) ;
      return a ;
    }
  else
    return a ;
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
    	printf (" %d (%d)\n\n", a->cle, niveau) ;

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
      return 1 + nombre_cles_arbre (a->fgauche) + nombre_cles_arbre (a->fdroite) ;
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

Dico detruire_cle_arbre (Dico a, int cle)
{
    Dico AC = rechercher_cle_arbre(a,cle) ;
    Dico AP = NULL ;
    Dico AD = NULL ;

  // Si la cle est absente ou l'arbre vide, renvoie l'arbre tel quel
  if((a == NULL) || (AC == NULL))
    return a ;
  // Si on supprime la racine : le fils droit devient la racine
  // Puis on ajoute l'arborescence du fils droit a ce nouvel arbre
  else if(a->cle == cle)
  {
    if(a->fdroite == NULL)
      return a->fgauche ;
    AC = a->fdroite ;
    if(a->fgauche != NULL)
      ajouter_noeud(a->fdroite,a->fgauche);
    return AC;
  }
  // Si on supprime une cle au sein de l'arbre : On cherche la cle
  // Puis on stocke ses fils droit et gauche
  // On supprime la cle recherchee et son arborescence
  // Enfin, on ajoute les arbres stockes au nouvel arbre
  else
  {
    if(AC->fgauche != NULL)
      AP = AC->fgauche ;
    if(AC->fdroite != NULL)
      AD = AC->fdroite ;
    AC = rechercher_cle_sup_arbre(a, cle) ;
    if(cle < AC->cle)
      AC->fgauche = NULL ;
    if(cle > AC->cle)
      AC->fdroite = NULL ;
    if(AP != NULL)
      ajouter_noeud(a, AP) ;
    if(AD != NULL)
      ajouter_noeud(a, AD) ;
    return a;
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
