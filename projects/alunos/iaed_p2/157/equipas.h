#include <stdbool.h>
#include <stdlib.h>
#include "hash.h"

/* Tamanho maximo dos nomes de equipas/jogos */
#define WORD_SIZE 1024


/* Estrutura equipa */
typedef struct equipa {
    /* Ponteiro para string que guarda o nome */
    char * nome;

    /* Numero de jogos ganhos */
    int vitorias;
    
} * pt_equipa;


/* Nodes para equipas */
typedef struct node_equipa {
    /* Ponteiro para equipa */
    pt_equipa equipa;

    /* Ponteiro para proximo node*/
    struct node_equipa * next;

} * link_equipa;


/* PROTOTIPOS */

/* Inicializa todos os indices da tabela a NULL */
link_equipa * init_equipas(link_equipa * tabela);

/* Devolve um ponteiro para uma nova equipa com o nome dado */
pt_equipa nova_equipa(char * nome);

/* Devolve ponteiro para equipa correspondente ao nome, caso nao exista devolve NULL */
pt_equipa procura_equipa(char * nome, link_equipa * equipas);

/* True caso a equipa exista, False caso contrario*/
bool equipa_existe(char * nome, link_equipa * equipas);

/* Liberta o espaco alocado para a equipa e para o seu nome */
void free_equipa(pt_equipa equipa);

/* Insere a equipa dada no respetivo lugar na tabela */
void insere_equipa_tabela(pt_equipa equipa, link_equipa * equipas);

/* Compara dois carateres, usada no qsort da funcao g (main) */
int compara(const void * a, const void * b);

/* Devolve o maior numero de vitorias das equipas */
int max_vitorias(link_equipa * equipas);
