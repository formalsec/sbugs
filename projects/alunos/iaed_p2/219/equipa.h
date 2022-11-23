#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXINPUT 3071	/*maximo de caracteres do input*/

typedef struct equipa{
	char *nome;
	int ganhos;          /*n de jogos ganhos da equipa*/
	struct equipa *equipa_seguinte, *equipa_anterior;
}equipa;

typedef struct {
	struct equipa *head, *last;
	int num_equipas;	/*contador de equipas*/
}lista_equipas;

/**
 * Cria uma equipa vazia
 * @return equipa *nova_equipa - equipa nova 
 */
equipa* cria_equipa();

/**
 * Cria uma lista de equipas vazia
 * @return lista_equipas *nova_lista - lista de equipas
 */
lista_equipas* cria_lista_equipas();

/**
 * Preenche a equipa com os argumentos dados como input
 * @param equipa *eq - equipa a preencher    
 * @param char *nome - nome da equipa
 */
void preenche_equipa(equipa *eq, char* nome);

/**
 * Adiciona a equipa dada como argumento a lista de equipas
 * @param equipa *eq - equipa a adicionar a lista 
 * @param lista_equipas *l_equipas - lista a qual se vai adicionar a equipa
 */
void adiciona_equipa(equipa *eq, lista_equipas *l_equipas);

/**
 * Elimina a lista de equipas dada como argumento
 * @param lista_equipas *l_equipas - lista das equipas 
 */
void free_equipas(lista_equipas *l_equipas);


