/* Michele Gusella 5AI 1/10/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nome "xmlconv"
#define versione "1.0"

/* Opzioni:
 * input file
 * output file
 * help
 * version
*/
void controlla(char **argv, int i)
{
	if(strcmp(argv[i], "-h") == 0)
	{
		help();
	}
	
	if(strcmp(argv[i], "-v") == 0)
	{
		version();
	}
}

void help()
{
	printf("Utilizzo: ./%s -i fileinput -o fileoutput", nome);
	quit();
}

void version()
{
	printf("Versione %s", versione);
	quit();
}

void quit()
{
	printf("\n");
	exit(0);
}

int main(int argc, char **argv)
{
	if(argc > 1)
	{
		for(int i = 1; i < argc; i++)
		{
			controlla(argv, i);
		}
	}
	
	return 0;
}
