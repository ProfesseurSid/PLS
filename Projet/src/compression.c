#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"
#include "binaryIO.h"

float Compression_Rate(char * f,char* fsor){
	float initial_size = 0;
	
	FILE * fp;
	fp = fopen(f,"r");
	fseek(fp,0L,SEEK_END);
	initial_size = ftell(fp);
	fclose(fp);
	
	FILE *fs;
	fs = fopen(fsor,"r");
	fseek(fs,0L,SEEK_END);
	initial_size = 100 * (1 - (ftell(fs)/initial_size));
	fclose(fs);
	
	return initial_size;
}

void compression(char* f,char* result_compress) {

uint8_t sortie_hexa;
uint32_t tampon = 0;
int taille = 0;
int nb_bits = 0;
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
Initialiser(&dico);

//fp est le fichier d'entrée. Ouverture du fichier d'entrée
FILE *fp;
fp = fopen(f,"r");

//Problème lors de l'ouverture du fichier
if(fp == NULL) {

	puts("Error : Couldn't open file");
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
	prefix = SequenceVersCode(w,wlength);
	mono = SequenceVersCode(&a,1);
	// printf("recherche : %c, taille : %i, tailleprefix : %i, taillemono : %i\n", w[0], wlength, prefix.longueur, mono.longueur);            // TRACE
	sortie = Chercher(dico , prefix , mono );

	//Si préfixe+mono est présent dans le dictionnaire
	if ( sortie == -1 ) {

		//On ralonge le préfixe.
		int* temp = malloc((wlength+1)*sizeof(int));
		// memcpy(temp,w,wlength-1);
		for(int l=0; l<wlength; l++)
			temp[l] = w[l];
		// *( temp + wlength-1 ) = a;
		temp[wlength] = a;
		wlength++;
		w = temp;
		// printf("on augmente\n");     // TRACE
		// free(temp);

	}

	else {
		//Affichage de l'indice dans le fichier de sortie

//		// TEST DE BINARYIO ___________________________________________________---

		nb_bits = Taille(sortie);
		// printf("\nTaille restante aa: %d\n", taille	);
		// printf("\nNb_bits taille : %d\n", nb_bits);
		if(taille + nb_bits > 32){
			// printf("\nTaille restante : %d\n", taille	);
			sortie_hexa = Retrait(&tampon, taille);
			taille -= 8;
			// printf("\nTaille restante : %d\n", taille	);
			printf("%x ", sortie_hexa);
			printf("\n\n On passe dans le > 32\n");
		}
		else{
			// printf("\nTaille restante : %d\n", taille	);
			Ajout(sortie, &tampon, nb_bits);
			taille += nb_bits;
		}

//		//_____________________________________________________________________---

		fprintf(result,"%d ",sortie);
		// fprintf(result," ");


		//Si l'insertion échoue (dictionnaire plein) : Affichage d'un caractère spécial et réinitialisation du dictionnaire
			// printf("uiui\n");
		if ( !Inserer( &dico , prefix , mono) ) {
			fprintf(result, "%d\n",dico.dict[256].code[0]);
			Initialiser(&dico);
		}

		//On replace w sur le dernier caractère lu
		wlength = 1;
		w = malloc ( wlength * sizeof (int) ) ;
		w[0] = a;
	}
}


//Affichage de l'indice dans le fichier de sortie  uint8_t Retrait(uint32_t *tampon, int taille_act){   void Ajout(int ind, uint32_t *tampon, int taille){
fprintf(result,"%d",sortie);
printf("Valeur du tampon avant vidage : %x \n",tampon);
while(taille > 8){
	sortie_hexa = Retrait(&tampon, taille);
	taille -= 8;
	printf("\nTaille restante : %d\n", taille	);
	printf("%x ", sortie_hexa);
}
sortie_hexa = Completion(&tampon, taille);
printf("%x ", sortie_hexa);
taille -= 8;
printf("Taille restante : %d\n", taille	);
//Fin des opérations. Fermeture des fichiers.
fclose(result);
fclose(fp);
}
