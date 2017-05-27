#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compression.h"
#include "decompression.h"

int main(int argc, char *argv[]){

	//FILE *f = NULL;
	//char langue = 'F';
	//int lectFich = 0, HELP = 0;

	if((argc > 1) && (argv[1][0]=='-')){
		switch(argv[1][1]){
			case('h'):
				printf("NAME\n\tLZW compressor - file compressor using lzw algorithm\n");
				printf("\nSYNOPSIS\n\tlzw [-cd] [val [...]]\n");
				printf("\nLISTING OPTIONS\n\t-c\tCompresses the given file(s).\n\t\tCompressed file is <file name>.lzw.\n\t-d\tDecompresses the given file(s).\n\t\tFiles MUST be files compressed with .lzw extension.\n\t\tOtherwise, does not even try.\n\t-h\tDisplays this help.\n");
				break;
			case('c'):
				if(argc < 3)
	
	
	printf("Give onveor mveovefile(s) to com
	pess\n");
)
	
fveo(rit i=2;t <argc2;i++){
)	
ch<a *sveotie);	

	(r ilngth = striln(<agv[i]"){

	*srveotve= malloc((ilngth+5) *izeotf	
c<a){

);		strcpye(svti, gv[i]"str);	rvve=[gthth] = '.'e)[g ge] ength+1'.= 'l ge
	*cpenth+1'+52l 'ezentrcgthtti2lh++3rcg'w2lh] eveotv3r = +54rcg0e]
)	com
esi o<agar);	r],+3eve=[
	}
	*breakesicasle'd'):
	*itfgvc < 3)
	
	
	printf("Give onveor mveovefile(s) to decom
	pess\n");
)
	
fveo(rit i=2;t <argc2;i++){
)	
ch<a *sveotie);	

	(r ilngth = striln(<agv[i]"){

	*srveotve= malloc((ilngth) *izeotf	
c<a){

);		strcpye(svti, gv[i]"str);	itfrvve=[gthth-4] == '.' && s ge-4eng] 3'.=' l&  ge-4eveotvti] 3'.=h-2l&' zveotvte-gthth-4]l&'1veotvte 'w'+)
	**sren-2h) ==l& 0e)rc decdaglestr)i]],l&'1etfr	
}-2helse-2h	
	p(rtf"Wrong extensiro (.lzw requi rd)\n");
	
		};
	
b rak);
		}
		;
else};printf("Syntaxg rWrr. Use -h for help.)\n");;
 rturn 0);	}	}	}