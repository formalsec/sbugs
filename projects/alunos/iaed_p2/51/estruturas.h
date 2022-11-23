#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

/******************************************************************************
 * Bibliotecas/Ficheiros:
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 * Estruturas:
******************************************************************************/

/************************* Lista duplamente ligada ***************************/

/* Estrutura que define o no' de uma lista (duplamente ligada) e as suas 
caracteristicas. */
typedef struct node {
    struct node *next, *previous;
    void *item;
} Node_list;

/* Estrutura que define uma lista duplamente ligada e as suas caracteristicas. */
typedef struct list {
    Node_list *head, *last;
} List;

/***************************** Arvore binaria ********************************/

/* Estrutura que define o no' de uma arvore binaria e as suas caracteristicas. */
typedef struct node_bt {
    struct node_bt *l, *r;
    int count, height, key;
    void **items;
} Node_bt;

/* Estrutura que define uma arvore binaria e as suas caracteristicas. */
typedef struct binary_tree {
    Node_bt *root;
} Bt;

/***************** Tabela de dispersao por procura linear ********************/

/* Estrutura que define uma tabela de dispersao por procura linear e as suas 
caracteristicas. */
typedef struct linear_probing {
    long size, cap;
    void **table;
} Lp;

/******************************************************************************
 * Abstracoes:
******************************************************************************/

/************************* Lista duplamente ligada ***************************/

/* Abstracao que, dado um ponteiro para um no' de uma lista, acede ao seu item. */
#define item_list(a) ((a)->item)

/* Abstracao que, dado um ponteiro para uma lista, acede ao primeiro elemento da 
lista. */
#define head_list(a) ((a)->head)

/* Abstracao que, dado um ponteiro para uma lista, acede ao ultimo elemento da 
lista. */
#define last_list(a) ((a)->last)

/***************************** Arvore binaria ********************************/

/* Abstracao que, dado um ponteiro para um no' de uma arvore binaria, acede aos 
seus itens. */
#define items_bt(a) ((a)->items)

/* Abstracao que, dado um ponteiro para um no' de uma arvore binaria, acede ao 
seu contador. */
#define count_bt(a) ((a)->count)

/* Abstracao que, dado um ponteiro para uma arvore binaria, acede 'a sua raiz. */
#define root_bt(a) ((a)->root)

/***************** Tabela de dispersao por procura linear ********************/

/* Abstracao que, dado um ponteiro para uma tabela de dispersao por procura 
linear, acede 'a tabela correspondente. */
#define table_lp(a) ((a)->table)

/******************************************************************************
 * Prototipos:
******************************************************************************/

/************************* Lista duplamente ligada ***************************/

/* mk_list: Funcao que cria uma nova lista vazia, e devolve um ponteiro para a 
mesma. */
List* mk_list();

/* add_node_list: Funcao que adiciona um item como o ultimo elemento de uma 
lista, e devolve o ponteiro do seu no'. 
 lista: parametro que representa o ponteiro para a lista.
 item: parametro que representa o item a inserir. */
Node_list* add_node_list(List *lista, void *item);

/* remove_node_list: Funcao que remove um elemento da lista onde esta inserido, 
e devolve o ponteiro da lista resultante.
 lista: parametro que representa o ponteiro para a lista.
 el: parametro que representa o ponteiro do no' do elemento a remover.
 free_item: parametro que representa o ponteiro para uma funcao que liberta 
toda a memoria associado aos itens do no'. */
List* remove_node_list(List *lista, Node_list *el, void free_item(void *));

/* print_list: Funcao que imprime todos os elementos de uma lista pela ordem 
de insercao.
 lista: parametro que representa o ponteiro para a lista.
 linha: parametro que representa a linha de input que esta a ser lida.
 print_item: parametro que representa o ponteiro para uma funcao que imprime 
cada item. */
void print_list(List *lista, int linha, void print_item(void *));

/* free_list: Funcao que liberta toda a memoria associada a uma lista.
 lista: parametro que representa o ponteiro para a lista.
 free_item: parametro que representa o ponteiro para uma funcao que liberta 
toda a memoria associado aos itens do no'. */
void free_list(List *lista, void free_item(void *));

/* empty_list: Funcao que indica se uma lista esta' vazia, ou nao.
 lista: parametro que representa o ponteiro para a lista. */
int empty_list(List *lista);

/***************************** Arvore binaria ********************************/

/* mk_bt: Funcao que cria uma nova arvore binaria vazia, e devolve um ponteiro 
para a mesma. */
Bt* mk_bt();

/* new_node_bt: Funcao que cria um novo no' de arvore binaria, e devolve o seu 
ponteiro.
 chave: parametro que representa a chave do no'.
 l: parametro que representa o ramo esquerdo do no'.
 r: parametro que representa o ramo direito do no'. */
Node_bt* new_node_bt(int chave, Node_bt *l, Node_bt *r);

/* heigth_bt: Funcao que determina e devolve o numero de niveis de uma arvore 
binaria.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
int height_bt(Node_bt *raiz);

/* rotL_bt: Funcao que executa uma rotacao esquerda numa arvore binaria, e 
devolve o ponteiro para a raiz da arvore resultante.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
Node_bt* rotL_bt(Node_bt *raiz);

/* rotD_bt: Funcao que executa uma rotacao direita numa arvore binaria, e 
devolve o ponteiro para a raiz da arvore resultante.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
Node_bt* rotR_bt(Node_bt *raiz);

/* get_balance_bt: Funcao que determina e devolve o parametro de balanceamento 
de uma arvore binaria.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
int get_balance_bt(Node_bt *raiz);

/* balance_bt: Funcao que faz o balanceamento de uma arvore binaria, e devolve 
o ponteiro para a raiz da arvore resultante.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
Node_bt* balance_bt(Node_bt *raiz);

/* max_bt: Funcao que procura e devolve o no' com a maior chave numa arvore 
binaria.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
Node_bt* max_bt(Node_bt *raiz);

/* add_node_bt: Funcao que adiciona um no' a uma arvore binaria, e devolve o 
ponteiro para a raiz da arvore resultante.
 chave: parametro que representa a chave que identifica o no' que vai ser 
adicionado.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
Node_bt* add_node_bt(int chave, Node_bt *raiz);

/* remove_node_bt: Funcao que remove um no' a uma arvore binaria, e devolve o 
ponteiro para a raiz da arvore resultante.
 chave: parametro que representa a chave que identifica o no' que vai ser 
removido.
 raiz: parametro que representa o ponteiro para a raiz da arvore.
 free_item: parametro que representa o ponteiro para uma funcao que liberta 
toda a memoria associado aos itens do no'. */
Node_bt* remove_node_bt(int chave, Node_bt *raiz, void free_item(void *));

/* search_bt: Funcao que procura e devolve um no' de uma arvore binaria.
 chave: parametro que representa a chave que identifica o no' que esta' a ser 
procurado.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
Node_bt* search_bt(int chave, Node_bt *raiz);

/* add_aux_bt: Funcao auxiliar da funcao add_item_bt.
 item: parametro que representa o ponteiro do item a adicionar.
 raiz: parametro que representa o ponteiro para a raiz da arvore.
 key: parametro que representa o ponteiro para uma funcao que acede 'a chave que
identifica o item numa arvore binaria. */
Node_bt* add_aux_bt(void *item, Node_bt *raiz, int key(void *));

/* add_item_bt: Funcao que adiciona um item a uma arvore binaria, e devolve o 
ponteiro para a raiz da arvore resultante.
 item: parametro que representa o ponteiro do item a adicionar.
 raiz: parametro que representa o ponteiro para a raiz da arvore.
 key: parametro que representa o ponteiro para uma funcao que acede 'a chave que
identifica o item numa arvore binaria. */
Node_bt* add_item_bt(void *item, Node_bt *raiz, int key(void *));

/* remove_item_bt: Funcao que remove um item a uma arvore binaria, e devolve o 
ponteiro para a raiz da arvore resultante.
 item: parametro que representa o ponteiro do item a remover.
 raiz: parametro que representa o ponteiro para a raiz da arvore.
 key: parametro que representa o ponteiro para uma funcao que acede 'a chave que
identifica o item numa arvore binaria.
 free_item: parametro que representa o ponteiro para uma funcao que liberta 
toda a memoria associado aos itens do no'. */
Node_bt* remove_item_bt(void *item, Node_bt *raiz, int key(void *),
 void free_item(void *));

/* free_aux_bt: Funcao auxiliar da funcao free_bt.
 raiz: parametro que representa o ponteiro para a raiz da arvore.
 free_item: parametro que representa o ponteiro para uma funcao que liberta 
toda a memoria associado aos itens do no'. */
void free_aux_bt(Node_bt *raiz, void free_item(void *));

/* free_bt: Funcao que liberta toda a memoria associada a uma arvore binaria.
 arvore: parametro que representa o ponteiro para a arvore binaria.
 free_item: parametro que representa o ponteiro para uma funcao que liberta 
toda a memoria associado aos itens do no'. */
void free_bt(Bt *arvore, void free_item(void *));

/* empty_bt: Funcao que indica se uma arvore binaria esta' vazia, ou nao.
 raiz: parametro que representa o ponteiro para a raiz da arvore. */
int empty_bt(Node_bt *raiz);

/***************** Tabela de dispersao por procura linear ********************/

/* mk_lp: Funcao que cria uma nova tabela de dispersao por procura linear, e 
devolve um ponteiro para a mesma.
 tamanho: parametro que representa o tamanho incial da tabela. */
Lp* mk_lp(long tamanho);

/* double_lp: Funcao que duplica o tamanho de uma tabela de dispersao, e devolve 
o ponteiro para a tabela de dispersao resultante. 
 lp: parametro que representa o ponteiro para a tabela de dispersao.
 key: parametro que representa o ponteiro para uma funcao que acede 'a chave que
identifica o item numa tabela de dispersao.
 hash: parametro que representa o ponteiro para uma funcao que distribui os 
indices para a tabela de dispersao. */
Lp* double_lp(Lp *lp, char* key(void *), long hash(void *, long));

/* add_item_lp: Funcao que adiciona um item a uma tabela de dispersao, e devolve 
o ponteiro para a tabela de dispersao resultante. 
 lp: parametro que representa o ponteiro para a tabela de dispersao.
 item: parametro que representa o ponteiro para o item a adicionar.
 key: parametro que representa o ponteiro para uma funcao que acede 'a chave que
identifica o item numa tabela de dispersao.
 hash: parametro que representa o ponteiro para uma funcao que distribui os 
indices para a tabela de dispersao. */
Lp* add_item_lp(Lp *lp, void *item, char* key(void *), long hash(void *, long));

/* search_item_lp: Funcao que procura um item numa tabela de dispersao, e 
devolve o seu ponteiro. 
 lp: parametro que representa o ponteiro para a tabela de dispersao.
 chave: parametro que representa a chave que identifica o item que esta' a ser 
procurado.
 key: parametro que representa o ponteiro para uma funcao que acede 'a chave que
identifica o item numa tabela de dispersao.
 hash: parametro que representa o ponteiro para uma funcao que distribui os 
indices para a tabela de dispersao. */
void* search_item_lp(Lp *lp, char* chave, char* key(void *),
 long hash(void *, long));

/* delete_item_lp: Funcao que elimina um item a uma tabela de dispersao, e 
devolve o seu ponteiro (para depois ser processado). 
 lp: parametro que representa o ponteiro para a tabela de dispersao.
 chave: parametro que representa a chave que identifica o item que esta' a ser 
procurado.
 key: parametro que representa o ponteiro para uma funcao que acede 'a chave que
identifica o item numa tabela de dispersao.
 hash: parametro que representa o ponteiro para uma funcao que distribui os 
indices para a tabela de dispersao. */
void* delete_item_lp(Lp *lp, char *chave, char* key(void *),
 long hash(void *, long));

/* free_lp: Funcao que liberta toda a memoria associada a uma tabela de 
dispersao. 
 lp: parametro que representa o ponteiro para a tabela de dispersao. */
void free_lp(Lp *lp);

#endif
