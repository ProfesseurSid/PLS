#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max(a,b) ((a)>(b)?(a):(b))

/* structure noeud presentee en cours */

typedef struct n {
  int cle; // L'indice dans le dictionnaire
  struct n *fgauche, *fdroite;
  int *code;
  int bal; // desequilibre
} Dico ;

/* type Arbre, pointeur vers un noeud */

typedef Dico *Arbre; 

/* n nouveau n a ajouter dans l'arbre a */

typedef struct
{
  int tete,queue,taille;
  Arbre *tab;
} file;


void init(file *f, int nbelem)
{
  f->tete = 0;
  f->queue = 0;
  f->taille = nbelem;
  f->tab = malloc(nbelem * sizeof(Arbre));
}

int empty(file *f)
{
  return f->tete == f->queue;
}

Arbre get(file *f)
{
  Arbre e;
  if(empty(f)) return NULL;
  else
  {
    e = f->tab[f->tete];
    f->tete = (f->tete + 1)%f->taille;
  }
  return e;
}

void put(file *f, Arbre a)
{
  f->tab[f->queue] = a;
  f->queue =(1 + f->queue)%f->taille;
}

int feuille (Arbre a)
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

Arbre ajouter_noeud (Arbre a, Arbre n)
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

Arbre rechercher_cle_arbre (Arbre a, int valeur)
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


void afficher_arbre (Arbre a, int niveau)
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

int hauteur_arbre (Arbre a)
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

void parcourir_arbre (Arbre a, int *t, int niveau)
{
  if (a == NULL)
    return ;
  
  t [niveau] = t [niveau] + 1 ;
  parcourir_arbre (a->fgauche, t, niveau+1) ;
  parcourir_arbre (a->fdroite, t, niveau+1) ;  

  return ;
}

void nombre_noeuds_par_niveau (Arbre a)
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

int nombre_cles_arbre (Arbre a)
{
  if (a == NULL)
    return 0 ;
  else
    {
      return 1 + nombre_cles_arbre (a->fgauche) + nombre_cles_arbre (a->fdroite) ;
    }
}



Arbre cle_superieure_arbre (Arbre a, int valeur, Arbre *sup)
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

Arbre rechercher_cle_sup_arbre (Arbre a, int valeur)
{
  Arbre ptrouve ;
  Arbre psup = NULL ;
    
  ptrouve = cle_superieure_arbre (a, valeur, &psup) ;
  return ptrouve ;
  
}

Arbre rotationDroite(Arbre a){
  // Je deviens le fils droit de mon fils gauche
  if (a != NULL){  
    Arbre NR = a->fgauche ;
    if(NR!=NULL){
      a->fgauche = NR->fdroite ;
      Arbre Pred = rechercher_cle_sup_arbre(a, a->cle) ;
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

Arbre rotationGauche(Arbre a){
  // Je deviens le fils gauche de mon fils droit
  if (a != NULL){
    Arbre NR = a->fdroite ;
    if(NR != NULL){
      a->fdroite = NR->fgauche ;
      Arbre Pred = rechercher_cle_sup_arbre(a, a->cle) ;
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

Arbre doubleRotationGauche(Arbre a){
  // Je deviens le fils gauche du fils gauche de mon fils droit
  a->fdroite = rotationDroite(a->fdroite) ;
  return rotationGauche(a) ;
}

Arbre doubleRotationDroite(Arbre a){
  // Je deviens le fils droit du fils droit de mon fils gauche
  a->fgauche = rotationGauche(a->fgauche) ;
  return rotationDroite(a) ;
}

Arbre Equilibrage(Arbre a){
  // Selon l'algorithme donne dans le polycopie
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

Arbre ajouter_cle (Arbre a, int cle)
{
  Arbre n ;
  Arbre ptrouve ;
  
  /* 
     ajout de la clé. Creation du noeud n qu'on insere 
    dans l'arbre a
  */

  ptrouve = rechercher_cle_arbre (a, cle) ;

  if (ptrouve == NULL)
  {
    n = (Arbre) malloc (sizeof(noeud)) ;
    n->cle = cle;
    n->fgauche = NULL ;
    n->fdroite = NULL ;
    n->bal = 0 ;
    a = ajouter_noeud (a, n) ;
    Arbre AC=rechercher_cle_sup_arbre(a, n->cle) ;
    while(AC!=NULL && AC->bal<2 && AC->bal>-2){
      AC->bal = hauteur_arbre(AC->fdroite) - hauteur_arbre(AC->fgauche) ;
      if (AC->bal<2 && AC->bal>-2)
        AC = rechercher_cle_sup_arbre(a, AC->cle) ;
    }

    if (AC != NULL){
      Arbre Pred = rechercher_cle_sup_arbre(a, AC->cle) ;
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

Arbre cle_inferieure_arbre (Arbre a, int valeur, Arbre *inf)
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

Arbre rechercher_cle_inf_arbre (Arbre a, int valeur)
{
  Arbre ptrouve ;
  Arbre pinf = NULL ;
    
  ptrouve = cle_inferieure_arbre (a, valeur, &pinf) ;
  return ptrouve ;  
}

int EquilibreComplet1 (Arbre a)
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

int EquilibreComplet2 (Arbre a)
{

  if (a == NULL)
    return 1 ;

  if ((a->fgauche != NULL && a->fdroite == NULL) || (a->fgauche == NULL && a->fdroite != NULL))
    return 0 ;

  return (EquilibreComplet2 (a->fgauche) && EquilibreComplet2 (a->fdroite)) ; 
}

Arbre lire_arbre (char *nom_fichier)
{
  FILE *f ;
  int cle;
  Arbre a = NULL;
  
  f = fopen (nom_fichier, "r") ;

  while (fscanf (f, "%d", &cle) != EOF)
    {
      a = ajouter_cle (a, cle) ;
    }
    
  fclose (f) ;

  return a ;
}

Arbre detruire_cle_arbre (Arbre a, int cle)
{
  Arbre AC = NULL ;
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
    Arbre AP = NULL ;
    Arbre AD = NULL ;
    Arbre Temp = NULL ;
    AC = rechercher_cle_arbre(a, cle) ;

    if(AC != NULL){ // Ne dois pas pouvoir se produire grace au tout premier test, mais est une securite supplementaire
      if(AC->fgauche != NULL)
        AP=AC->fgauche ;
      if(AC->fdroite != NULL)
        AD=AC->fdroite ;
      Arbre Pred = rechercher_cle_sup_arbre(a, cle) ;
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

int trouver_cle_min (Arbre a)
{
  Arbre AC = NULL;

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

void imprimer_liste_cle_triee (Arbre a)
{
  Arbre AC = a;
  int min;
  
  // Si la racine n'est pas NULL,
  // On envoie la fonction sur l'arbre gauche
  // Puis on affiche la cle courante
  // Enfin, on envoie la fonction sur l'arbre gauche
  if(a == NULL){
    return;
  }
  else{
    imprimer_liste_cle_triee(a->fgauche);
    printf("%d ", a->cle);
    imprimer_liste_cle_triee(a->fdroite);
  }
}

//Afiche les clefs de l'arbre par niveau
void parcourir_arbre_largeur (Arbre a)
{
  file liste, stock;
  init(&liste, nombre_cles_arbre(a));
  init(&stock, nombre_cles_arbre(a));

  // A chaque iteration, ajoute les fils des noeuds de la file
  // A la seconde file, puis affiche lesdits noeuds
  // Et opere la meme chose de la seconde a la premiere, pour reduire le nombre de tours
  // Et eviter une simple copie de la seconde a la premiere file
  put(&liste, a);
  for(int i=0;i<=(hauteur_arbre(a)/2)+1;i+=2){
    if(!empty(&liste))
      printf("hauteur %i : ", i);
    while(!empty(&liste)){
      Arbre AC = get(&liste);
      if(AC->fdroite!=NULL)
        put(&stock, AC->fdroite);
      if(AC->fgauche!=NULL)
        put(&stock, AC->fgauche);
      printf("%i ", AC->cle);
    }
    printf("\n");

    if(!empty(&stock))
      printf("hauteur %i : ", i+1);
    while(!empty(&stock)){
      Arbre AC = get(&stock);
      if(AC->fdroite!=NULL)
        put(&liste, AC->fdroite);
      if(AC->fgauche!=NULL)
        put(&liste, AC->fgauche);
      printf("%i ", AC->cle);
    }
    printf("\n");
  }
  printf("\n");
}



Arbre union_deux_arbres (Arbre a1, Arbre a2)
{
  // Si l'un ou les deux arbres sont NULL, renvoie l'autre
  if(a1 == NULL && a2 == NULL)
    return NULL ;
  else if(a2 == NULL)
    return a1 ;
  else if(a1 == NULL)
    return a2 ;
  // Sinon, si la racine de a2 n'est pas dans a1, 
  // L'ajoute a l'arbre resultat
  // puis cherche dans les fils de a2 les cles non presentes
  else{
    if(rechercher_cle_arbre(a1, a2->cle) == NULL)
        a1 = ajouter_cle(a1, a2->cle) ;
    a1 = union_deux_arbres(a1, a2->fgauche) ;
    a1 = union_deux_arbres(a1, a2->fdroite) ;
    return a1 ;
  }
}

Arbre intersection_deux_arbres (Arbre a1, Arbre a2)
{
  if(a1 != NULL){
    // Si la cle est absente du deuxieme arbre,
    // on la retire de l'arbre resultat
    if(rechercher_cle_arbre(a2, a1->cle) == NULL){
      a1=detruire_cle_arbre(a1, a1->cle) ;
      a1=intersection_deux_arbres(a1, a2) ;
    }
    // Sinon, l'arbre resultat devient l'union de l'intersection des ses fils et a2
    // a quoi on ajoute la cle actuelle
    else if(a1->fgauche != NULL && a1->fdroite != NULL)
      a1=ajouter_cle(union_deux_arbres(intersection_deux_arbres(a1->fgauche, a2), intersection_deux_arbres(a1->fdroite, a2)), a1->cle);
    else if(a1->fgauche != NULL)
      a1=ajouter_cle(intersection_deux_arbres(a1->fgauche, a2), a1->cle);
    else if(a1->fdroite != NULL)
      a1=ajouter_cle(intersection_deux_arbres(a1->fdroite, a2), a1->cle);
    else
      return a1;
  }
}


//Dit si l'ensemble des clefs de a1 sont inclues dans a2
int inclusion_arbre (Arbre a1, Arbre a2)
{
  // Renvoie le booleen "la cle actuelle est dans a2, et l'ensemble des cles de mes fils aussi"
  if(a1!=NULL){
    return ((rechercher_cle_arbre(a2, a1->cle)!=NULL) && inclusion_arbre(a1->fgauche, a2) && inclusion_arbre(a1->fdroite, a2));
  }
  else{
    return 1;
  }

}



int main (int argc, char**argv)
{
  Arbre a,a1,a2 ;
  int x ;
  int bool ;
  Arbre  ptrouve = NULL ;

  if (argc != 3)
    {
      fprintf (stderr, "il manque le parametre nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre (argv[1]) ;
  a1 = lire_arbre (argv[2]) ;

  printf("------\na1 : |\n------\n\n") ;
  afficher_arbre (a,0) ;
  printf("------\na2 : |\n------\n\n") ;
  afficher_arbre (a1,0) ;
  printf("---------\na1Ua2 : |\n---------\n\n") ;
  a2 = union_deux_arbres(a,a1) ;
  afficher_arbre (a2,0) ;

  printf("Tests d'inclusion :\n") ;
  printf(">> a1 contenu dans a1Ua2 : %i\n", inclusion_arbre(a, a2)) ;
  printf(">> a2 contenu dans a1Ua2 : %i\n", inclusion_arbre(a1, a2)) ;
  printf(">> a1Ua2 contenu dans a1Ua2 : %i\n", inclusion_arbre(a2, a2)) ;
  printf(">> a1Ua2 contenu dans a1 : %i\n\n", inclusion_arbre(a2, a)) ;

  a = lire_arbre (argv[1]) ;
  a1 = lire_arbre (argv[2]) ;

  printf("------\na1 : |\n------\n\n") ;
  afficher_arbre (a,0) ;
  printf("------\na2 : |\n------\n\n") ;
  afficher_arbre (a1,0) ;
  printf("---------------\na1 inter a2 : |\n---------------\n\n") ;
  a2 = intersection_deux_arbres(a,a1) ;
  afficher_arbre (a2,0) ;

  printf("\n\nTests de ajout/suppression :\n") ;
  a = lire_arbre (argv[1]) ;
  a1 = lire_arbre (argv[2]) ;
  printf("Arbre de depart :\n") ;
  afficher_arbre(a1, 0) ;
  printf("suppression de 28...\n") ;
  a1 = detruire_cle_arbre(a1, 28) ;
  afficher_arbre(a1, 0) ;
  printf("ajout de 28...\n") ;
  a1 = ajouter_cle(a1, 28);
  afficher_arbre(a1, 0) ;
  printf("suppression de 15...\n") ;
  a1 = detruire_cle_arbre(a1, 15) ;
  afficher_arbre(a1, 0) ;
  printf("ajout de 15...\n") ;
  a1 = ajouter_cle(a1, 15) ;
  afficher_arbre(a1, 0) ;
  printf("ajout de 16...\n") ;
  a1 = ajouter_cle(a1, 16) ;
  afficher_arbre(a1, 0) ;
  printf("suppression de 2...\n") ;
  a1 = detruire_cle_arbre(a1, 2) ;
  afficher_arbre(a1, 0) ;
  printf("suppression de 5...\n") ;
  a1 = detruire_cle_arbre(a1, 5) ;
  afficher_arbre(a1, 0) ;
  printf("suppression de la racine...\n") ;
  a1 = detruire_cle_arbre(a1, a1->cle) ;
  afficher_arbre(a1, 0) ;


  // a = lire_arbre (argv[1]) ;
  // a1 = lire_arbre (argv[2]) ;

  printf("Parcours en largeur de l'arbre resultat :\n") ;
  parcourir_arbre_largeur(a1) ;

  printf("Cles triees de a1 : ") ;
  imprimer_liste_cle_triee(a) ;
  printf("\n") ;


/*
  printf("Clé min : %d\n",trouver_cle_min(a));

  printf ("Hauteur %d\n", hauteur_arbre (a)) ;

  nombre_noeuds_par_niveau (a) ;

  printf ("Nombre cles de l'arbre %d\n", nombre_cles_arbre (a)) ;
*/
/*
  bool = EquilibreComplet1 (a) ;
  if (bool = 1)
    printf ("Methode 1: Arbre equilibre complet\n") ;
  else
    printf ("Methode 1: Arbre n'est pas equilibre complet\n") ;
*/
/*  
  bool = EquilibreComplet2 (a) ;
  if (bool = 1)
    printf ("Methode 2: Arbre equilibre complet\n") ;
  else
    printf ("Methode 2: Arbre n'est pas equilibre complet\n") ;
*/

  /*
    Appels des fonctions de recherche de cles
  */
/*
  printf ("Entrez une cle a rechercher\n") ;

  scanf ("%d", &x) ;

  ptrouve = rechercher_cle_arbre (a, x) ;

  if (ptrouve != NULL)
    printf ("la cle %d est dans l'arbre\n", x) ;
  else
    printf ("la cle %d n'est pas dans l'arbre\n", x) ;

  ptrouve = rechercher_cle_sup_arbre (a, x) ;

  if (ptrouve != NULL)
    printf ("la cle sup de %d est %d\n", x, ptrouve->cle) ;
  else
    printf ("il n'y a pas de cle sup pour %d\n", x) ;

  ptrouve = rechercher_cle_inf_arbre (a, x) ;

  if (ptrouve != NULL)
    printf ("la cle inf de %d est %d\n", x, ptrouve->cle) ;
  else
    printf ("il n'y a pas de cle inf pour %d\n", x) ;
*/
}
