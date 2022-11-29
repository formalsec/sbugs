#include "funcoes_aux.h"

/*Numero maximo de caracteres no nome de uma equipa (+ '\0').*/
#define NOME_EQUIPA 1024

/*Estrutura Equipa.*/
typedef struct Equipa
{
	/*Nome da equipa.*/
	char *nome;
	/*Numero de vitorias da equipa.*/
	int numero_vitorias;
	/*Ponteiro para a proxima equipa com a mesma chave da hashtable.*/
	struct Equipa *next;
}Equipa;

void freeEquipa(Equipa* equipa);

void printEquipa(Equipa* equipa, int conta_linhas);

void printNome_Equipa(Equipa* equipa, int conta_linhas);

void soma_vitorias(Equipa* equipa);

void subtrai_vitorias(Equipa* equipa);

Equipa* novaEquipa(char *nome);
