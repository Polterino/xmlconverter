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
	printf("Uso: ./%s [Opzione/i]\n   -h Menu' di aiuto\n   -v Versione del programma\n   -i fileinput\n   -o fileoutput", nome);
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
	
	if(argc > 1)	// Controlla se ci sono parametri inseriti e agisce di conseguenza
	{
		for(int i = 1; i < argc; i++)
		{
			controlla(argv, i);
		}
	}
	input = stdin;
	printf("%s", input);
	//Controllare l'estensione per l'output
	//printf("%s\n%s\n", estensione_file(*input), estensione_file(*output));
	ezxml_t fileinput = ezxml_parse_file(input);
	file = fopen(output, "w");
	
	if(file)
	{				
		/*
		 ezxml_child(ezxml_t puntatore, char stringa)
		 Ritorna il puntatore figlio della variabile "puntatore" che si chiama "stringa"
		  
		 ezxml_attr(ezxml_t puntatore, char stringa)
		 Ritorna il valore (stringa) dell'attributo "stringa" del puntatore "puntatore"
		  
		*/
		
		ezxml_t macchina = ezxml_child(fileinput, "Machine");
		fprintf(file, "Nome della macchina: %s\n", ezxml_attr(macchina, "name"));
		
		fprintf(file,"Sistema Operativo: %s\nDisco rigido:\n", ezxml_attr(macchina, "OSType"));
		
		ezxml_t media = ezxml_child(macchina, "MediaRegistry");
		ezxml_t dischi = ezxml_child(media, "HardDisks");
		ezxml_t disco = ezxml_child(dischi, "HardDisk");
		int esco = 0;											// Variabile booleana
		for(; esco == 0; disco = disco -> next)
		{
			fprintf(file, "   Nome: %s   Formato: %s\n", ezxml_attr(disco, "location"), ezxml_attr(disco, "format"));
			if(disco -> next == NULL)
				esco = 1;
		}
		
		ezxml_t hardware = ezxml_child(macchina, "Hardware");
		ezxml_t boot = ezxml_child(hardware, "Boot");
		ezxml_t ordine_boot = ezxml_child(boot, "Order");
		fprintf(file, "Ordine di boot:\n");
		for(esco = 0; esco == 0; ordine_boot = ordine_boot -> next)
		{
			fprintf(file, "   Posizione: %s   Device: %s\n", ezxml_attr(ordine_boot, "position"), ezxml_attr(ordine_boot, "device"));
			if(ordine_boot -> next == NULL)
				esco = 1;
		}
		
		ezxml_t memoria = ezxml_child(hardware, "Memory");
		fprintf(file, "Ram: %sMb\nScheda di rete:\n", ezxml_attr(memoria, "RAMSize"));
		
		ezxml_t network = ezxml_child(hardware, "Network");
		ezxml_t scheda_rete = ezxml_child(network, "Adapter");
		ezxml_t interfaccia;
		
		for(esco = 0; esco == 0; scheda_rete = scheda_rete -> next)
		{
			if(ezxml_attr(scheda_rete, "MACAddress") != NULL)		// Se la scheda di rete ha un mac vuol dire che è attiva
			{
				interfaccia = ezxml_child(scheda_rete, "BridgedInterface");
				fprintf(file,"   Slot: %s   Indirizzo Mac: %s   Tipo: %s   Interfaccia: %s\n", ezxml_attr(scheda_rete, "slot"),
					ezxml_attr(scheda_rete, "MACAddress"), ezxml_attr(scheda_rete, "type"), ezxml_attr(interfaccia, "name"));
			}
			if(scheda_rete -> next == NULL)
				esco = 1;
		}
		
		ezxml_t scheda_audio = ezxml_child(hardware, "AudioAdapter");
		fprintf(file, "Scheda audio:\n   Codec: %s   Driver: %s\n", ezxml_attr(scheda_audio, "codec"), ezxml_attr(scheda_audio, "driver"));
		
		ezxml_t rtc = ezxml_child(hardware, "RTC");
		fprintf(file, "Real Time Clock: %s\n", ezxml_attr(rtc, "localOrUTC"));
		
		ezxml_free(fileinput);
		fclose(file);
	}
	
	return 0;
}
