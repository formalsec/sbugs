#ifndef _TABELA_DISPERSAO_
#define _TABELA_DISPERSAO_

#include <stdio.h>
#include <string.h>
#include "listas.h"
#include "constantes.h"


/* Funcao de Dispersao */
int hash(char *v, int M);

/* Estrutura das tabelas */
typedef struct estr_tab_jg {
    lista** cabecas_jg;
} tabela_jogo;

typedef tabela_jogo* tab_jg;

typedef struct estr_tab_eq {
    lista_equipa** cabecas_eq;
} tabela_equipa;

typedef tabela_equipa* tab_ep;



/* Verifica se a tabela equipa eh vazia. */
int eh_vazia_tabela_equipa(const tabela_equipa* tabela, int M);

/* Verifica se a tabela jogo eh vazia. */
int eh_vazia_tabela_jogo(const tabela_jogo* tabela, int MJ);



/* Cria tabela de dispersao de equipas. */
tabela_equipa* cria_tabela_equipa(int M);                

/* Cria tabela de dispersao de jogos. */
tabela_jogo* cria_tabela_jogo(int MJ);



/* Liberta toda a memoria associada a uma tabela_equipa (struct tabela_equipa) */
void liberta_tabela_equipa(tabela_equipa* tab_libertar, int M);

/* Liberta toda a memoria associada a uma tabela_jogo (struct tabela_jogo) */
void liberta_tabela_jogo(tabela_jogo* tab_libertar, int MJ);



/* Retorna ponteiro para lista_equipa inserida ou cria caso nao exista a lista. */
lista_equipa* insere_ou_cria_lista_equipa(tabela_equipa* tabela, char *equipa, int M);

/* Retorna ponteiro para lista_equipa pesquisada ou NULL caso nao exista a lista. */
lista_equipa* pesquisa_lista_equipa(tabela_equipa* tabela, char* equipa, int M);

/* Retorna ponteiro para lista inserida ou cria caso nao exista a lista. */
lista* insere_ou_cria_lista_jogo(tabela_jogo* tabela, char *jogo, int MJ);

/* Retorna ponteiro para lista_jogo pesquisada ou NULL caso nao exista a lista. */
lista* pesquisa_lista_jogo(tabela_jogo* tabela, char* jogo, int MJ);



/* Retorna o valor de max_vitorias */
int retorna_max_vitorias_tabela(const tabela_equipa* tabela, int M);

/* Retorna quantidade de equipas com max_vitorias */
int retorna_contador_max_vitorias_tabela(const tabela_equipa* tabela, int M, \
                                            int max_vitorias);




#endif