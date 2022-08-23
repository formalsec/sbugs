#ifndef _AVL_
#define _AVL_

#include <stdlib.h>
#include "equipa.h"

typedef char* Chave;

/*A chave de uma equipa corresponde ao seu nome*/
#define chave(a) (a->nome)

/*Estrutura dos nos de uma AVL*/
typedef struct avl_node{
    pEquipa equipa;
    int altura;
    struct avl_node* l; /*Ponteiro para a parte da arvore a esquerda do no*/
    struct avl_node* r; /*Ponteiro para a parte da arvore a direita do no*/
} *avl_link;

/*Estrutura da AVL*/
typedef struct avl_str{
    avl_link head; /*Link que aponta para a raiz da AVL.*/
} *Avl;

void avl_init(Avl*);

/*Funcoes basicas da AVL*/

avl_link avl_cria(pEquipa);
avl_link avl_insere(avl_link, pEquipa);
avl_link avl_procura(avl_link, Chave);
avl_link avl_verifica(Avl, Chave, int, int);

/*Balanceamento da arvore*/

avl_link avl_balanco(avl_link);
avl_link avl_rotacao_L(avl_link);
avl_link avl_rotacao_R(avl_link);
avl_link avl_rotacao_LR(avl_link);
avl_link avl_rotacao_RL(avl_link);

int avl_obtem_fator(avl_link);
int avl_obtem_altura(avl_link);
int avl_atualiza_altura(avl_link);

/*Tratamento das melhores equipas*/

int avl_obtem_max_ganhos(avl_link, int);
void avl_print_melhores(avl_link, int, int);

/*Libertacao de memoria*/

void avl_free_h(avl_link);
void avl_free(Avl);

#endif