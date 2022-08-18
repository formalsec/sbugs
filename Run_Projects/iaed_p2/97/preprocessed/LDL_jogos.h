#ifndef LDL_JOGOS
#define LDL_JOGOS

#include "Jogos.h"

typedef struct elem_j {
    struct elem_j *prox, *ante;
    Item_j *jogo;
} elem_j;

typedef struct  {
    elem_j *inicio, *fim;
} lista;

/* Cria nova lista vazia */
lista* cria_lista_jogos();

/* Liberta toda a memoria associada a lista */
void apaga_lista_jogos(lista *l);

/* Apaga a memoria associada a lista, sem apagar o seu conteudo */
void liberta_lista_jogos(lista *l);

/* Adiciona o Item el como o ultimo elemento da lista */
void adiciona_jogo_lista(lista *l, Item_j *el);

/* Retira o elemento el (e correspondente jogo) da lista */
void remove_jogo_lista(lista *l, elem_j *el);

/* Retorna um ponteiro para o elem que contem o nome nome, NULL caso contrario */
elem_j* encontra_jogo_lista(lista *l, char *nome);

/* Retorna o jogo do elemento el */
Item_j* acede_jogo(elem_j *el);

/* Retorna o primeiro elemento da lista l */
elem_j* acede_inicio_lista_jogos(lista *l);

/* Retorna o elemento seguinte a el */
elem_j* prox_elem(elem_j* el);

#endif