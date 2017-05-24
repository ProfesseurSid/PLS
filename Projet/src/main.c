#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compression.h"
#include "decompression.h"

int main(int argc, char *argv[]){

	//FILE *f = NULL;
	//char langue = 'F';
	//int lectFich = 0, HELP = 0;

	if(argc > 1){
		if(argv[1][0]=='-'){
			switch(argv[1][1]){
				case('h'):
					printf("NAME\n\tLZW compressor - file compressor using lzw algorithm\n");

					printf("\nSYNOPSIS\n\tlzw [-cd] [val [...]]\n");

					printf("\nLISTING OPTIONS\n\t-c\tCompresses the given file(s).\n\t\tCompressed file is <file name>.lzw.\n\t-d\tDecompresses the given file(s).\n\t\tFiles MUST be files compressed with .lzw extension.\n\t\tOtherwise, does not even try.\n\t-h\tDisplays this help.\n");
					//HELP = 1;
					break;
				case('c'):
					/*lectFich = 1;
					f = fopen(argv[2],"r");
					if(f == NULL){
						printf("Erreur lors de l'ouverture du fichier de donnée\n");
						lectFich = 0;
					}*/
					if(argc < 3)
						printf("Give one or more file(s) to compress\n");

					for(int i=2; i<argc; i++){
						char *sortie;
						int length = strlen(argv[i]);
						sortie = malloc((length+5)*sizeof(char));
						strcpy(sortie, argv[i]);
						sortie[length] = '.';
						sortie[length+1] = 'l';
						sortie[length+2] = 'z';
						sortie[length+3] = 'w';
						sortie[length+4] = 0;
						compression(argv[i],sortie);
					}
					break;
				case('d'):
					//langue = argv[2][0];
					if(argc < 3)
						printf("Give one or more file(s) to decompress\n");

					for(int i=2; i<argc; i++){
						char *sortie;
						int length = strlen(argv[i]);
						sortie = malloc((length)*sizeof(char));
						strcpy(sortie, argv[i]);
						if(sortie[length-4] == '.' && sortie[length-3] == 'l' && sortie[length-2] == 'z' && sortie[length-1] == 'w'){
							sortie[length-4] = 0;
							decodage(argv[i],sortie);
						}
						else
							printf("Wrong extension (.lzw required)\n");
					}
					break;
			}
		}
	}
	else
		printf("Syntax error. Use -h for help.\n");
/*
	if(argc > 3){
		if(argv[1][0]=='-'){
			switch(argv[3][1]){
				case('f'):
					lectFich = 1;
					f = fopen(argv[4],"r");
					if(f == NULL){
						printf("Erreur lors de l'ouverture du fichier de donnée\n");
						lectFich = 0;
					}
					break;
				case('l'):
					langue = argv[4][0];
			}
		}
	}

	if(lectFich){
		lire_fichier(f,langue);
		fclose(f);
	}
	else if(!HELP)
		saisie_clavier(langue);
*/
	return 0;
}
