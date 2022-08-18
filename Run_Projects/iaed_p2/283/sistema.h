#ifndef __SISTEMA__
#define __SISTEMA__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabela_jogo.h"
#include "tabela_team.h"
#include "lista.h"

/*Ponteiro base do meu programa que guarda um ponteiro para a hash table dos jogos, a hash table das equipas e a lista de jogos */


typedef struct sistema{
	struct link **tabela_jogos;
	struct link_t **tabela_teams;
	struct node *lista;

} Sistema;

/* Liberta o meu sistema todo apagando tudo da base de dados*/

void liberta_sistema(Sistema *s);

/* Inicia o meu sistema inicializando as duas hash tables e a lista ligada de jogos */

Sistema *init_sistema();

#endif