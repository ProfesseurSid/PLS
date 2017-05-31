#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compression.h"
#include "decompression.h"

int main(int argc, char *argv[]) {
	char *sortie = NULL;
	int length;
	// lecture des arguments
	if(argc > 1) {
		if(argv[1][0]=='-') {
			switch(argv[1][1]) {

				//Aide
				case('h'):
					printf("NAME\n\tLZW compressor - file compressor using lzw algorithm\n");
					printf("\nSYNOPSIS\n\tlzw [-cd] [val [-s [val]]]\n");
					printf("\nLISTING OPTIONS\n\t-c\tCompresses the given file(s).\n\t\tCompressed file is <file name>.lzw.\n\t-d\tDecompresses the given file.\n\t\tFiles MUST be files compressed with .lzw extension.\n\t\tOtherwise, does not even try.\n\t-s\tUsed with -d.\n\t\tRedirects the output to the file whose name is given.\n\t-h\tDisplays this help.\n");
					break;

				//Commande compression
				case('c'):

					if(argc < 3){
						printf("Give a file to compress\n");
						exit(1);
					}

					//ajout d'extension
					length = strlen(argv[2]);
					sortie = malloc((length+5)*sizeof(char));
					strcpy(sortie, argv[2]);
					sortie[length]   = '.';
					sortie[length+1] = 'l';
					sortie[length+2] = 'z';
					sortie[length+3] = 'w';
					sortie[length+4] =  0 ;
					compression(argv[2],sortie);
					free(sortie);
					break;

				//DECOMPRESSION
				case('d'):
					if(argc < 3){
						printf("Give a file to decompress\n");
						exit(1);
					}
					//Verification du format d'extension
					length = strlen(argv[2]);
					sortie = malloc((length)*sizeof(char));
					strcpy(sortie, argv[2]);
					sortie[length-4] = 0;
					if(argv[2][length-4] == '.' && argv[2][length-3] == 'l' && argv[2][length-2] == 'z' && argv[2][length-1] == 'w') {
						if(argc > 4){
							if(argv[3][0] == '-' && argv[3][1] == 's'){
								length = strlen(argv[4]);
								sortie = realloc(sortie, (length+1)*sizeof(char));
								strcpy(sortie, argv[4]);
							}
						}
						decodage(argv[2],sortie);
					}
					else
						printf("Wrong extension (.lzw required)\n");

					break;
			}
		}
		else
			printf("Wrong option. Use -h for help.\n");
	}
	else
		printf("Syntax error. Use -h for help.\n");

	return 0;
}
