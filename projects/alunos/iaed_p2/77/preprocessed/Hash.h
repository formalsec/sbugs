#ifndef _HASH_
#define _HASH_

/* Tamanho das Hash Tables */
#define TAM_HASH 79999

#include "Estruturas.h"
#include <string.h>

/* Funcao que calcula a posicao de um nome numa tabela */
int dispersao(char *nome);

/* Funcao que cria e inicializa a tabela usada para guardar os jogos */
p_jogo* inicializa_jogos();

/* Funcao que cria e inicializa a tabela usada para guardar as equipas */
p_equipa* inicializa_equipas();

/* Funcao que insere um jogo na tabela devida */
void insere_jogo(p_jogo novo, p_jogo *tab_j);

/* Funcao que insere uma equipa na tabela devida */
void insere_equipa(p_equipa nova, p_equipa *tabela_equipas);

/* Funcao que retorna o ponteiro do jogo chamado "nome" e indica a sua posicao */
p_jogo encontra_jogo(char *nome, p_jogo *tab_j, int *posicao);

/* Funcao que retorna o ponteiro da equipa chamada "nome" */
p_equipa encontra_equipa(char *nome, p_equipa *tabela_equipas);

/* Funcao que elimina um jogo da tabela devida */
void remove_jogo(p_jogo *tab_j, int *posicao);


#endif