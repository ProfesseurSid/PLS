#include<stdio.h>
#include<stdlib.h>
#include "dict.h"

void compression(char* f,char* result_compress) {

int* w;
int a;

int wlength=1;

Dico dico;

Code prefix, mono;

remove(result_compress);

initialiser(dico);

File *fp;
fp = fopen(f,"r");

if(fp == NULL) {

	puts("Error : file");
	exit(-1);
	
	}
	
	
w = malloc ( wlength * sizeof (int) ) ;
*w = fgetchar(fp) ;
File* result;
result = fopen(result_compress,"a");

while ( !feof(fp) ){
	a = fgetchar(fp)
	sortie = chercher(dico , prefix = SequenceVersCode(w,wlength) , mono = SequenceVersCode(a,1) );
	
	if ( sortie == -1 ) {
	
		wlength++;
		int* temp = malloc(wlength*sizeof(int));
		memcpy(temp,w,wlength-1);
		*( temp + wlength-1 ) = a;
		w = temp;
		free(temp);

		}

	else {
		
		fprintf(result,sortie);
		
		if ( !inserer( dico , prefix , mono) ) {
			fprintf(result, dico.dict[255].code[0]);
			intialiser(dico)
		
			}
		
		*w = a;

		}
	}
    


fprintf(result,sortie);
fclose(result);
fclose(f);
}





