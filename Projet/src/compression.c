#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"
#include "binaryIO.h"

float Compression_Rate(FILE * f,FILE* fsor){
	float initial_size = 0;
	fseek(f,0,SEEK_END);
	initial_size = ftell(f);
	fseek(fsor,0,SEEK_END);
	initial_size = 100 * (1 - (ftell(fsor)/initial_size));

	return initial_size;
}

void compression(char* f,char* result_compress) {
	uint8_t sortie_hexa;
	uint32_t tampon = 0;
	int nb_bits_restant = 32;
	int* w = NULL;
	int a;
	//La longueur du mot courant
	int wlength=1;

	int sortie;

	//Le dictionnaire
	Dico dico;

	Code prefix, mono;

	printf("compression du fichier %s...\n", f);
	//Si un fichier porte le nom du fichier à produire on le supprime
	remove(result_compress);
	//Initialisation du dictionnaire
	Initialiser(&dico);

	//fp est le fichier d'entrée. Ouverture du fichier d'entrée
	FILE *fp;
	fp = fopen(f,"r");
	// printf("compression du fichier %s...\n", f);

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

				Ajout(sortie, &tampon, &nb_bits_restant, dico);
				sortie_hexa = Retrait(&tampon, &nb_bits_restant, dico);
				fprintf(result,"%c",sortie_hexa);
				if(nb_bits_restant < nb_bits_requis(nombre_elements(dico))){
					sortie_hexa = Retrait(&tampon, &nb_bits_restant, dico);
					fprintf(result,"%c",sortie_hexa);
				}


			//Si l'insertion échoue (dictionnaire plein) : Affichage d'un caractère spécial et réinitialisation du dictionnaire
			if ( !Inserer( &dico , prefix , mono) ) {
				Initialiser(&dico);
			}

			//On replace w sur le dernier caractère lu
			wlength = 1;
			w = malloc (wlength * sizeof (int) ) ;
			w[0] = a;
		}
	}

	//Affichage de l'indice dans le fichier de sortie  uint8_t Retrait(uint32_t *tampon, int taille_act){   void Ajout(int ind, uint32_t *tampon, int taille){
	if(nb_bits_restant != 32){
		sortie_hexa = Retrait(&tampon, &nb_bits_restant, dico);
		fprintf(result,"%c", sortie_hexa);
	}

	printf("fichier %s compresse avec succes !\nTaux de compression : %f\n", f, Compression_Rate(fp, result));

	//Fin des opérations. Fermeture des fichiers.
	fclose(result);
	fclose(fp);
}
