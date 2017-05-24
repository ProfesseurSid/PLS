#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compression.h"
#include "decompression.h"

int main(int argc, char *argv[]) { 
	// lecture des arguments
	if(argc > 1) { 
		if(argv[1][0]=='-') { 
			switch(argv[1][1]) { 
				
				//Aide
				case('h'): 
					printf("NAME\n\tLZW compressor - file compressor using lzw algorithm\n"); 
					printf("\nSYNOPSIS\n\tlzw [-cd] [val [...]]\n"); 
					printf("\nLISTING OPTIONS\n\t-c\tCompresses the given file(s).\n\t\tCompressed file is <file name>.lzw.\n\t-d\tDecompresses the given file(s).\n\t\tFiles MUST be files compressed with .lzw extension.\n\t\tOtherwise, does not even try.\n\t-h\tDisplays this help.\n"); 
					break; 
					
				//Commande compression
				case('c'): 
					
					if(argc < 3) 
						printf("Give one or more file(s) to compress\n"); 
					
					//ajout d'extension
					for(int i=2; i<argc; i++) { 
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
					
				//DECOMPRESSION 
				case('d'): 
					if(argc < 3) 
						printf("Give one or more file(s) to decompress\n"); 

					for(int i=2; i<argc; i++) { 
						char *sortie; 
						int length = strlen(argv[i]); 
						sortie = malloc((length)*sizeof(char)); 
						strcpy(sortie, argv[i]); 
						
						//Verification du format d'extension 
						if(sortie[length-4] == '.' && sortie[length-3] == 'l' && sortie[length-2] == 'z' && sortie[length-1] == 'w') { 
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
 
	return 0; 
} 
