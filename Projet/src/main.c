#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compression.h"
#include "decompression.h"
//#include "piece.h"
//#include "coup.h"
//#include "plateau.h"
//#include "vt100.h"
//#include "fonc_carac.h"

/*
void saisie_clavier(char langue){
	affiche_func_param_t sortie;
	char coup[4];
	echiquier_t plateau;
	couleur_t dernierJoueur = Noir;

	init(plateau);
	afficher_plateau(plateau, sortie, langue);
	switch(langue){
		case('A'): printf("Give your move (column-line-column-line) : ");break;
		default: printf("Entrez un coup (colonne-ligne-colonne-ligne) : ");
	}

	do{
		fscanf(stdin, "%s", coup);
		if(feof(stdin))
			switch(langue){
				case('A'): printf("Good bye !\n");break;
				default: printf("Au revoir !\n");
			}
		else if(creer_coup_interact(coup, dernierJoueur, plateau)){
			afficher_plateau(plateau, sortie, langue);
			switch(langue){
				case('A'): printf("Next move : ");break;
				default: printf("Coup suivant : ");
			}
			// On change de joueur
			if(dernierJoueur == Blanc)
				dernierJoueur = Noir;
			else
				dernierJoueur = Blanc;
		}
		else
			switch(langue){
				case('A'): printf("\nWrong move. Next move : ");break;
				default: printf("\nMauvais coup. Coup suivant : ");
			}
	}while(!feof(stdin));

	printf("\n");

}

void lire_fichier(FILE *f, char langue)
{
	char coup[4];
	char trash;
	coup_t *ListeDeCoups = NULL;
	coup_t *QueueListeDeCoups = NULL;
	echiquier_t plateau;
	affiche_func_param_t sortie;

	init(plateau);
	afficher_plateau(plateau, sortie, langue);

	while(!feof(f))
	{
		fscanf(f,"%c%c%c%c%c",&coup[0],&coup[1],&coup[2],&coup[3],&trash);
		creer_coup(coup, &ListeDeCoups, &QueueListeDeCoups);
	}

	init(plateau);
	while(ListeDeCoups != NULL){
		printf("    %s\n\n", ListeDeCoups->comment);
		jouer_coup(plateau, &ListeDeCoups);
		afficher_plateau(plateau, sortie, langue);
		scanf("%c",&trash);
	}
}
*/
int main(int argc, char *argv[]){

	//FILE *f = NULL;
	//char langue = 'F';
	//int lectFich = 0, HELP = 0;

	if(argc > 1){
		if(argv[1][0]=='-'){
			switch(argv[1][1]){
				case('h'):
					printf("NAME\n\tLZW compressor - file compressor using lzw algorithm\n");
					printf("\nSYNOPSIS\n\tchess [-cd] [val [...]]\n");
					printf("\nLISTING OPTIONS\n\t-c\tCompresses the given file(s).\n\t\tCompressed file is <file name>.lzw.\n\t-d\tDecompresses the given file(s).\n\t\tFiles MUST be files compressed with .lzw extension. Otherwise, does not even try.\n\t-h\tDisplays this help.\n");
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

					for(int i=2; i<argc-2; i++){
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

					for(int i=2; i<argc-2; i++){
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
