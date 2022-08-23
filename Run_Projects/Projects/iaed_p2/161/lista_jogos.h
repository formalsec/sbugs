#include "jogo.h"


typedef struct node_jogo
{
    pJogo jogo; /* ponteiro para um jogo */
    struct node_jogo *next; /* ponteiro para o proximo elemento  da lista */

} *link_jogo; /* link eh um ponteiro para elemento da lista */

typedef struct lista
{
    link_jogo cabeca, ultimo; 

} lista; /* lista de jogos */


/* prototipos ---------------------------------------------------------------------------------- */

/* inicializa uma lista de jogos devolve o ponteiro para a lista */
lista* inicializa_lista_jogos();

/* adiciona um jogo no fim da lista */
void adiciona_jogo_lista(lista*, pJogo );

/* remove um jogo da lista e devolve o ponteiro para esse jogo */
pJogo remove_jogo_lista(lista*, char*);

/* escreve a informacao de todos os jogos da lista */
void print_lista_jogos(lista*, unsigned int);

/* liberta a memoria da lista e dos jogos */
void destroi_lista_jogos(lista*);