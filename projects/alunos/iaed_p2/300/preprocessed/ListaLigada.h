#ifndef ListaLigada
#define ListaLigada

typedef struct stru_node /* Ponteiro para um jogo */
{
    struct stru_node *next, *previous;
    struct Jogo *jogo;
} node;

typedef struct /* Estrutura da Lista*/
{
    node *head, *last;
} list;

#include "Jogos.h"

list *mk_list();                                                                        /* Funcao que cria uma lista */
void free_list(list *l);                                                                /* Funcao que da free ha lista e ao node */
void free_node(node *n);                                                                /* Funcao que da free ao node */
void rm_node(list *l, node *n);                                                         /* Funcao que remove o node da lista */
node *add_last(list *l, char *n, char *equipa1, char *equipa2, int score1, int score2); /* Funcao que adiciona um node ha lista */
void printList(node *head, int nl);                                                     /* Funcao que da print a todos os jogos que estao na lista */
#endif