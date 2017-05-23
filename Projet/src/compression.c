#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dict.h"

void compression(char* f,char* result_compress) {

int* w;
int a;
//La longueur du mot courant
int wlength=1;

int sortie;

//Le dictionnaire
Dico dico;

Code prefix, mono;

//Si un fichier porte le nom du fichier à produire on le supprime
remove(result_compress);

//Initialisation du dictionnaire
Initialiser(dico);

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

//Tant que la fin du fichier n'est pas atteinte :
while ( !feof(fp) ){

	//a est le caractère suivant
	a = fgetc(fp);
	sortie = Chercher(dico , prefix = SequenceVersCode(w,wlength) , mono = SequenceVersCode(&a,1) );

	//Si préfixe+mono est présent dans le dictionnaire
	if ( sortie == -1 ) {

		//On ralonge le préfixe.
		wlength++;
		int* temp = malloc(wlength*sizeof(int));
		memcpy(temp,w,wlength-1);
		*( temp + wlength-1 ) = a;
		w = temp;
		free(temp);

		}

	else {
		//Affichage de l'indice dans le fichier de sortie
		fprintf(result,"%d",sortie);

		//Si l'insertion échoue (dictionnaire plein) : Affichage d'un caractère spécial et réinitialisation du dictionnaire
		if ( !Inserer( dico , prefix , mono) ) {
			fprintf(result, "%d",dico.dict[255].code[0]);
			Initialiser(dico);

			}

		//On replace w sur le dernier caractère lu
		*w = a;

		}
	}


//Affichage de l'indice dans le fichier de sortie
fprintf(result,"%d",sortie);

//Fin des opérations. Fermeture des fichiers.
fclose(result);
fclose(fp);
}
