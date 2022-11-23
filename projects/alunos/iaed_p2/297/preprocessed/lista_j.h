#ifndef LISTA_J_H
#define LISTA_J_H
#include <stdlib.h>
#include "tabela_jogos.h"

/*  == Representacao do tipo estrutura de dados
 
 *  - lista simplesmente ligada cujo cada no contem um jogo
 *  - lista ordenada de acordo com a insercao de jogo
 *  - referencias head e last

 *  == Fim da representacao */

/*---------------------------Estruturas----------------------------*/

/*  Estrutura de um no com um jogo */
typedef struct str_node{
    jogo* jogo;
    struct str_node* next, *prev;
}node;

/*  Estrutura da lista de jogos inseridos */
typedef struct str_list{
    node* head, *last;
}lista;

/*-----------------Prototipos->Funcoes Principais------------------*/

/*  Inicializa uma lista alocando o espaco suficiente */
lista* inic_lista(void);

/*  Insere um jogo na lista de jogos inseridos como sendo o ultimo */
void push_last(jogo* j, lista* l);

/*  Procura um jogo cujo nome e dado. Se nao existir retorna NULL,
 *  caso contrario o no do jogo */
node* procura_l(const char* nome_j, lista* l);

/*  Remove um no com um jogo libertando a memoria respetiva dele */
void remove_node(node* n, lista* l);

/*  Liberta toda a memoria alocada dos nos e da lista */
void free_lista(lista* l);

#endif