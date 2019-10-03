/* Michele Gusella 5AI 1/10/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Variabili statiche
#define nome "xmlconv"
#define versione "1.0"

// Variabili globali
char *input = "", *output = "";

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
	
	if(strcmp(argv[i], "-i") == 0)
	{
		input = argv[i + 1];
	}
	
	if(strcmp(argv[i], "-o") == 0)
	{
		output = argv[i + 1];
	}
}

char *estensione_file(char *nome)
{
	char *punto = strrchr(nome, '.');
    if(!punto || punto == nome)
		return "";
    return punto + 1;
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
	FILE *file;
	char prova[8];
	
	if(argc > 1)	// Controlla i parametri inseriti e agisce di conseguenza
	{
		for(int i = 1; i < argc; i++)
		{
			controlla(argv, i);
		}
	}
	printf("%s\n%s\n", estensione_file(*input), estensione_file(*output));
	if(input != "" && output != "")
	{
		file = fopen(input, "r");
		
		
		
		fclose(file);
		
		file = fopen(output,"w");
		
		fclose(file);
	}
	else
	{
		printf("Attenzione! Nessun file di input o di output inseriti");
		quit();
	}
	
	return 0;
}
