#ifndef _INTERFACE_
#define _INTERFACE_

#include "hash.h"
#include "equipa.h"
#include "jogo.h"
#include "arvore.h"

/* ABTRACOES */

typedef char * chave; /* chave de procura de equipas ou jogos -> o seu nome */
#define NOTFOUND (NULL)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* ESTRUTURAS */

/* caracterizacao da estrutura par_res */
typedef struct par_res
{
    int maximo; /* inteiro - maximo: numero maximo de vitorias */
    int num_venc; /* inteiro - num_venc: numero de equipas que o atingiram */
} par_resultado;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* CONSTANTES */

/* flags de controlo gerais */
#define MAX_CAR 1024 /* numero maximo de caracteres por palavra lida do stdin */
#define EXECUTA 2 /* flag que significa que comandos estao e vao ser executados */
#define NAO_EXECUTA 0 /* flag que significa que nao ha mais comandos a executar */
#define UNIT_FILA 1 /* uma unidade - 1 fila */

/* flags de erro */
#define NAO_EQ -1 /* flag que indica que uma equipa nao existe */
#define EQ_REP -2 /* flag que indica que uma equipa ja existe */
#define NAO_JG -3 /* flag que indica que um jogo nao existe */
#define JG_REP -4 /* flag que indica que um jogo ja existe */

/* flags de controlo especificas */
#define FILA -7 /* flag que indica que se vai adicionar um jogo/equipa a uma fila */
#define TABELA -8 /* flag que indica que se vai adicionar um jogo/equipa a uma tabela */
#define NOMAX -9 /* flag que indica que nao ha um valor maximo de vitorias */
#define EQ -5 /* flag que indica que algo e uma equipa */
#define JG -6 /* flag que indica que algo e um jogo */


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* GESTAO GERAL */

/* funcao que inicializa a memoria */
void inicializa(fila equipas, fila jogos, fila jogos_ord, fila equipas_ord);
/* funcao que liberta toda a memoria inicializada */
void liberta(fila equipas, fila jogos, fila jogos_ord, fila equipas_ord);
/* funcao que escreve um certo erro de introducao de input */
void escreve_erro(int nL, int erro); 
/* funcao que procura um item -> equipa ou jogo <- pela chave (nome) */
void * encontra(fila Lst, chave c, int flag);

/* INTERFACE HASH <-> JOGO */

/* funcao que junta um jogo a uma fila (ou tabela de filas - hash) */
void junta_j(fila jogos, jogo j, int flag);
/* funcao que encontra um jogo numa fila */
jogo encontra_j_lst(fila jogos, chave nome); 
/* funcao que encontra um jogo numa tabela de filas - hash */
jogo encontra_j_tab(fila jogos, chave nome);
/* funcao que retira um jogo de uma fila (ou tabela de filas - hash) */
void tira_j(fila jogos, jogo j, int flag);
/* funcao que altera o score de um jogo */
void muda_score(jogo j, int s1, int s2);
/* funcao que imprime uma fila de jogos */
void escreve_j_lst(int nL, fila jogos);

/* INTERFACE HASH <-> EQUIPA */

/* funcao que junta uma equipa a uma fila (ou tabela de filas - hash) */
void junta_e(fila equipas, equipa e, int flag);
/* funcao que encontra uma equipa numa fila (auxiliar a encontra_e_tab) */
equipa encontra_e_lst(fila equipas, chave nome); 
/* funcao que encontra uma equipa numa tabela de filas - hash */
equipa encontra_e_tab(fila equipas, chave nome);
/* funcao que incrementa/decrementa as vitorias de uma equipa */
void muda_vitorias(equipa e, char op);
/* funcao que encontra o numero maximo de vitorias */
par_resultado maximo_vitorias(fila equipas_ord);

/* INTERFACE ARVORE <-> EQUIPA */

/* funcao que constroi uma arvore a partir duma fila, filtrando-a */
arvore * ARVbuild(arvore * raiz, fila equipas_ord, int maximo, int num_venc);


#endif

