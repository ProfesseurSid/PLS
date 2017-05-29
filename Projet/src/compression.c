#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"

void compression(char* f,char* result_compress) {

int* w;
int a;
//La longueur du mot courant
int wlength=1;
int sortie;

//Initialisation du dictionnaire
//Le dictionnaire
Dico dico = NULL;

// Les préfixes, suffixes
Code prefix, mono;

//Si un fichier porte le nom du fichier à produire on le supprime
remove(result_compress);

//Initialisation du dictionnaire
Initialiser(&dico);

//fp est le fichier d'entrée. Ouverture du fichier d'entrée
FILE *fp;
fp = fopen(f,"r");

//Problème lors de l'ouverture du fichier
if(fp == NULL) {

	puts("Error : file");
	exit(-1);

	}


//Allocation d'une case pour stocker le caractère lu
w = malloc ( wlength * sizeof (int) ) ;
*w = fgetc(fp) ;

//Création et ouverture du fichier de sortie.
FILE* result;
result = fopen(result_compress,"w");

//Tant que la fin du fichier n'est pas atteinte
while ( !feof(fp) ){
	//a est le caractère suivant
	a = fgetc(fp);
	prefix = SequenceVersCode(w,wlength);
	mono = SequenceVersCode(&a,1);
	sortie = Chercher(dico , prefix , mono );

	//Si préfixe+mono est présent dans le dictionnaire
	if ( sortie == -1 ) {
		//On ralonge le préfixe.
		int* temp = malloc((wlength+1)*sizeof(int));
		for(int l=0; l<wlength; l++)
			temp[l] = w[l];
		temp[wlength] = a;
		wlength++;
		w = temp;
	}
	else {
		//Affichage de l'indice dans le fichier de sortie
		fprintf(result,"%d ",sortie);
		//On replace w sur le dernier caractère lu & réinitialisation de wlength
		wlength = 1;
		w = realloc ( w, wlength * sizeof (int) ) ;
		w[0] = a;
	}
}


//Affichage de l'indice dans le fichier de sortie
fprintf(result,"%d",sortie);

//Fin des opérations. Fermeture des fichiers.
fclose(result);
fclose(fp);
}
