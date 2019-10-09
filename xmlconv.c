/* Michele Gusella 5AI 1/10/2019

	Costruire un programma in C che dato in input il file xml di una macchina virtuale Virtualbox produca un report in formato "Umano" in formato solo testo o HTML (o RTF).

	Prevedere il flusso dati stdin e stdout oppure indicando i file da riga di comando oppure l'immissione di tali file da programma con appositi parametri da riga di comando.

	Se opportuno usare stderr.

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Librerie per xml
#include "lib/ezxml.h"
#include "lib/ezxml.c"

//Variabili statiche
#define versione "1.0"

// Variabili globali
static const char nome[] = "xmlconv";
char *input = "";
char *output = "";

/* Opzioni:
 * input file
 * output file
 * help
 * version
*/

// Dichiarazioni delle funzioni
void help(void);
void version(void);
void quit(void);


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

/*char *estensione_file(char *nome)
{
	char *punto = strrchr(nome, '.');
    if(!punto || punto == nome)
		return "";
    return punto + 1;
} */

void help()
{
	printf("Uso: ./%s [Opzione]\n   -h Menu' di aiuto\n   -v Versione del programma\n   -i fileinput\n   -o fileoutput", nome);
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
	char *prova;
	
	if(argc > 1)	// Controlla se ci sono parametri inseriti e agisce di conseguenza
	{
		for(int i = 1; i < argc; i++)
		{
			controlla(argv, i);
		}
	}
	
	//Controllare l'estensione per l'output
	//printf("%s\n%s\n", estensione_file(*input), estensione_file(*output));
		
	if(input != "" && output != "")		//Se l'utente ha inserito il file di input e di output
	{
		//Input
		//file = fopen(input, "r");
		
		ezxml_t fileinput = ezxml_parse_file(input);	
		fileoutput = fopen(output, "w");									
		
		
		ezxml_t getMeToMachine = ezxml_child(fileinput, "tipo");		
		nome = ezxml_attr(getMeToMachine, "nome");				
		fprintf(fileoutput, "Nome della macchina: %s\n", nome);	

		ezxml_t getMeToOS = ezxml_child(fileInput, "Machine");
		tipoOS = ezxml_attr(getMeToOS, "OSType"); 						
		fprintf(fileOutput,"Sistema Operativo: %s\n", tipoOS);	
		
		ezxml_t getMeToRam1 = ezxml_child(fileInput, "Machine");
		ezxml_t getMeToRam2 = ezxml_child(getMeToRam1, "Hardware");
		ezxml_t grandezzaRam = ezxml_child(getMeToRam2, "Memory");
		sizeRam = ezxml_attr(grandezzaRam, "RAMSize"); 					
		fprintf(fileOutput,"RAM size: %sMb\n", sizeRam);		
		
		ezxml_free(fileInput);
		fclose(fileOutput);	
		
		fclose(file);
		
		
		/*Output
		file = fopen(output, "w");
		
		
		
		fclose(file); */
	}
	
	else if(input != "" && output == "")
	{
		
	}
	
	else if(input == "" && output == "")
	{
		
	}
	
	return 0;
}
