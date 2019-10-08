/* Michele Gusella 5AI 1/10/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Librerie per xml
#include "lib/xml.h"

//Variabili statiche
#define versione "1.0"

typedef struct xml_document* structxml;
typedef struct xml_node* nodoxml;
typedef struct xml_string* stringaxml;

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

char *estensione_file(char *nome)
{
	char *punto = strrchr(nome, '.');
    if(!punto || punto == nome)
		return "";
    return punto + 1;
}

void help()
{
	printf("Uso: ./%s -i fileinput -o fileoutput", nome);
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
	char *prova = "";
	
	if(argc > 1)	// Controlla i parametri inseriti e agisce di conseguenza
	{
		for(int i = 1; i < argc; i++)
		{
			controlla(argv, i);
		}
	}
	//Controllare l'estensione per l'output
	//printf("%s\n%s\n", estensione_file(*input), estensione_file(*output));
	
	uint8_t* source = ""
		"<Root>"
			"<Hello>World</Hello>"
			"<This>"
				"<Is>:-)</Is>"
				"<An>:-O</An>"
				"<Example>:-D</Example>"
				"<Example>:-D</Example>"
			"</This>"
		"</Root>"
	;
		
	if(input != "" && output != "")		//Se l'utente ha inserito il file di input e di output
	{
		//Input
		file = fopen(input, "rb");
		
		uint8_t *buffer = 0;
		long lunghezza;

		if(file)
		{
			fseek(file, 0, SEEK_END);
			lunghezza = ftell(file);
			fseek(file, 0, SEEK_SET);
			buffer = malloc(lunghezza);
			
			if(buffer)
			{
				fread(buffer, 1, lunghezza, file);
			}
		}		
		
		fclose(file);
		
		//printf("%s", buffer);
		
		/*
		structxml documento = xml_parse_document(buffer, strlen(buffer));
		
		if(!documento)
		{
			printf("Couldn't parse document\n");
			quit();
		}
		nodoxml root = xml_document_root(documento);
		
		nodoxml root_hello = xml_node_child(root, 0);
		stringaxml hello = xml_node_name(root_hello);
		stringaxml world = xml_node_content(root_hello);
		
		uint8_t* hello_0 = calloc(xml_string_length(hello) + 1, sizeof(uint8_t));
		uint8_t* world_0 = calloc(xml_string_length(world) + 1, sizeof(uint8_t));
		xml_string_copy(hello, hello_0, xml_string_length(hello));
		xml_string_copy(world, world_0, xml_string_length(world));

		printf("%s %s\n", hello_0, world_0);
		free(hello_0);
		free(world_0);
		
		nodoxml root_this = xml_node_child(root, 1);
		printf("Root/This has %lu children\n", (unsigned long)xml_node_children(root_this));
		xml_document_free(documento, false);
		*/
		
		//Output
		file = fopen(output, "w");
		if(buffer)
			fprintf(file, "%s", buffer);
			//printf("%s", buffer);
		fclose(file);
	}
	
	else
	{
		printf("Attenzione! Nessun file di input o di output inserito");
		quit();
	}
	
	return 0;
}
